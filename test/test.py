"""
To set up a simplified system for the glucose stimulated insulin secretion in pancreatic beta cells.

"""
from __future__ import print_function, division
import IMP.atom
import IMP.algebra
import IMP.rmf
import IMP.core
import RMF
import IMP.container
import IMP.display
import numpy as np
import OrganelleFactory
import time
import random
import IMP.insulinsecretion

# set time
start=time.time()

# --------------------

# Define functions

# --------------------

def convert_time_ns_to_frames(time_ns, step_size_fs):
    '''
    Given time in nanoseconds time_ns and step size in femtosecond
    step_size_fs, return an integer number of frames greater or equal
    to 1, such that time_ns*step_size_fs is as close as possible to
    time_ns.
    '''
    FS_PER_NS= 1E6
    time_fs= time_ns * FS_PER_NS
    n_frames_float= (time_fs+0.0) / step_size_fs
    n_frames= int(round(n_frames_float))
    return max(n_frames, 1)

def get_random_vesicles_in_cytoplasm(outer_sphere, inner_sphere, N_vesicles, R_vesicle):
    '''
    Return random vectors inside the cell (=outer) sphere and
    outside the nuclear envelope (=inner) sphere, and make sure they do not overlap 
    with each other and with the boundaries.
    '''
    V_vesicles = []
    while True:
        R_inner= inner_sphere.get_radius() + R_vesicle
        R_outer= outer_sphere.get_radius() - R_vesicle
        vector = IMP.algebra.get_random_vector_in(outer_sphere)
        if R_outer > vector.get_magnitude() > R_inner:
            if len(V_vesicles) == 0:
                V_vesicles.append(list(vector))
            elif len(V_vesicles) > 0:
                overlap = False
                for V in V_vesicles:
                    if (vector-V).get_magnitude() <= 2*R_vesicle:
                        overlap = True
                        break
                if not overlap:
                    V_vesicles.append(list(vector))
        if len(V_vesicles) == N_vesicles:
            return V_vesicles

def get_uniform_cacium_channel_on_cell(outer_sphere, N_CaChannel):
    '''
    Return random vectors for calcium channels on cell membrane (=outer).
    '''
    V_cachanel = IMP.algebra.get_uniform_surface_cover(outer_sphere, N_CaChannel)
    random.shuffle(V_cachanel)
    return V_cachanel
        
def create_nucleus(m, R):
    '''
    Generate a coarse-grained spherical nuclear envelope
    of radius R in model m
    '''
    p= IMP.Particle(m, "md")
    xyzr = IMP.core.XYZR.setup_particle(p)
    xyzr.set_coordinates_are_optimized(True)
    xyzr.set_coordinates([0,0,0])
    xyzr.set_radius(R)
    IMP.display.Colored.setup_particle(p, IMP.display.get_display_color(2))
    IMP.atom.Hierarchy.setup_particle(p)
    return p

def do_stats_after_optimize(vesicles):
    '''write out insulin vesicle coordinates along time'''
    coord = {}
    distance = []
    mature = []
    docked = []
    for i, g in enumerate(vesicles):
        xyz = IMP.core.XYZ(g)
        coord[i] = [round(xyz.get_x(), 4), round(xyz.get_y(), 4), round(xyz.get_z(), 4)]
        distance.append(round(IMP.core.get_distance(IMP.core.XYZ(h_nucleus),IMP.core.XYZ(g)),4))
        mature.append(IMP.insulinsecretion.MaturationStateDecorator(g).get_state())
        docked.append(IMP.insulinsecretion.DockingStateDecorator(g).get_dstate())
    return coord, distance, mature, docked

# --------------------

# Set simulation parameters

# --------------------

# I. Parts parameters
L = 64000 # Length of our bounding box, A
R = 30250 # PBC radius, A
R_NUCLEUS = 18340 # NE radius, A
N_VESICLES = 200 # Number of vesicles
R_VESICLES = 1200 # Radius of vesicles, A
D_VESICLES = 2.3E-10 # diffusion coefficient of vesicles, A^2/fs.
R_CaChannel = 100 # Ca2+ microdomain radius, A
N_CaChannel = 451 # Number of Ca2+ channels.
N_trough = 3 # Number of Ca2+ channels in the opening state at the trough
N_peak = 450 # Number of Ca2+ channels in the opening state at the peak

# II. Interaction parameters
K_BB = 1E-5  # Strength of the harmonic boundary box in kcal/mol/A^2
K_EXCLUDED = 1E-5 # Strength of lower-harmonic excluded volume score in kcal/mol/A^2
K_TRAFFIC = 0  # Strength of the force that pulls ready state vesicles towards the periphery in kcal/mol/A^2

VDOS_CONTACT_RANGE = R_CaChannel # contact range of vesicle surface to Ca2+ channel under which insulin vesicles are docked, A
VDOS_SLACK = 10 # slack for the ClosePairContainer of insulin vessicles and Ca2+ channels, A
VDOS_PERIOD = 10 # update the maturation secretion decorator periodically.

Oscillation = 80 # number of steps to update the Ca2+ channel opening state, Oscillation*OscillationPeriod = 800, 8s
OscillationPeriod = VDOS_PERIOD # oscillation period

ISOS_CUT_OFF = (R - R_NUCLEUS)/3 # cut-off from the NE surface to reset vesicles, has to be larger than R_vesicleS*2, A
ISOS_PERIOD = VDOS_PERIOD # update the maturation secretion decorator periodically.
READY_STATE = 100 # number of steps needed for the docked vesicles to secrete. READY_STATE*ISOS_PERIOD=1000, 10s

K_RDF = 0 # Coefficient for the rdf potential
PARAM_RDF = [-1.524e-20, 9.173e-16, -2.092e-11, 2.202e-07, -1.141e-03, 3.492e+00]

'''
---2.8mM - 477 insulin vesicles
-1.524e-20, 9.173e-16, -2.092e-11, 2.202e-07, -1.141e-03, 3.492e+00

---16.7mM - 547 insulin vesicles
-7.457e-21, 4.486e-16, -1.059e-11, 1.238e-07, -7.798e-04, 2.534e+00

---16.7mM-Ex4 - 699 insulin vesicles
3.137e-20, -1.491e-15, 2.269e-11, -9.993e-08, -3.162e-04, 2.529e+00
'''

# III. Time parameters
BD_STEP_SIZE_SEC= 1E-2 # a time step of 0.01 s
SIM_TIME_SEC= 10 # total simulation time, s
bd_step_size_fs= BD_STEP_SIZE_SEC * 1E+15
sim_time_ns= SIM_TIME_SEC * 1E+9
sim_time_frames= convert_time_ns_to_frames(sim_time_ns, bd_step_size_fs)
tot_frames = int(sim_time_frames/VDOS_PERIOD) # Total frames to save
RMF_DUMP_INTERVAL_NS= sim_time_ns / tot_frames
rmf_dump_interval_frames= convert_time_ns_to_frames(RMF_DUMP_INTERVAL_NS, bd_step_size_fs)

# --------------------

# Name output files

# --------------------

condition = 'c1'
repeat = '00'
'''
There are three conditions:
c0 - 2.8 Glu - 30 min
c1 - 16.7 Glu - 30 min
c2 - 16.7 Glu + Ex - 30 min
'''

f1=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_record.txt', 'w')
f2=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_secretion.xvg','w')
f3=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_coord.xvg','w')
f4=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_VESICLE-NE_distance.xvg','w')
f5=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_maturation.xvg','w')
f6=open(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_' + str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat_docked.xvg','w')

# --------------------

# Define model representation

# --------------------

# I. Nucleus and the cell
# Model:
m = IMP.Model()
# Root of parts hierarchy:
p_root= IMP.Particle(m, "root")
h_root = IMP.atom.Hierarchy.setup_particle(p_root)
# Outer bounding box for simulation:
bb = IMP.algebra.BoundingBox3D(IMP.algebra.Vector3D(-L/2, -L/2, -L/2), IMP.algebra.Vector3D(L/2, L/2, L/2))
# PBC cytoplasm bounding sphere:
pbc_sphere= IMP.algebra.Sphere3D([0,0,0], R)
# Nucleus:
p_nucleus= create_nucleus(m, R_NUCLEUS)
IMP.atom.Mass.setup_particle(p_nucleus, 1.0) # fake mass
h_nucleus= IMP.atom.Hierarchy(p_nucleus)
h_root.add_child(h_nucleus)
nucleus_sphere= IMP.core.XYZR(p_nucleus).get_sphere()

# II. Vesicles and Ca2+ channels
# Vectors for vesicles and Ca2+ channels
V_VESICLES = get_random_vesicles_in_cytoplasm(pbc_sphere, nucleus_sphere, N_VESICLES, R_VESICLES)
V_CaChannel = get_uniform_cacium_channel_on_cell(pbc_sphere, N_CaChannel)

# Vesicles hierarchy root:
p_vesicles_root= IMP.Particle(m, "Vesicles")
IMP.atom.Mass.setup_particle(p_vesicles_root, 1.0) # fake mass
h_vesicles_root= IMP.atom.Hierarchy.setup_particle(p_vesicles_root)
h_root.add_child(h_vesicles_root)

# Actual vesicles:
for i in range(N_VESICLES):
    grnf=OrganelleFactory.VesicleFactory(model= m, default_R= R_VESICLES, v =V_VESICLES[i])
    vesicle= grnf.create_vesicle("Vesicle_{}".format(i))
    h_vesicle= IMP.atom.Hierarchy(vesicle)
    #print(h_vesicle.get_children())
    h_vesicles_root.add_child(h_vesicle)
    IMP.atom.Diffusion(vesicle).set_diffusion_coefficient(D_VESICLES)
    #print(IMP.atom.Diffusion(vesicle).get_diffusion_coefficient())
    #print(IMP.insulinsecretion.DockingStateDecorator(vesicle).get_dstate())
    #print(IMP.core.XYZR(vesicle).get_radius())
    
# Calcium channel hierarchy root:
p_cachannel_root= IMP.Particle(m, "CaChannel")
IMP.atom.Mass.setup_particle(p_cachannel_root, 1.0) # fake mass
h_cachannel_root= IMP.atom.Hierarchy.setup_particle(p_cachannel_root)
h_root.add_child(h_cachannel_root)

# Actual cachannel:
for i in range(N_trough):
    cachannelf=OrganelleFactory.CaChannelFactory(model= m,default_R= R_CaChannel, v = V_CaChannel[i])
    cachannel= cachannelf.create_cachannel_with_State("CaChannel_{}".format(i), -1)
    h_cachannel= IMP.atom.Hierarchy(cachannel)
    h_cachannel_root.add_child(h_cachannel)
    
for i in range(N_trough, N_CaChannel):
    cachannelf=OrganelleFactory.CaChannelFactory(model= m,default_R= R_CaChannel, v = V_CaChannel[i])
    cachannel= cachannelf.create_cachannel_with_State("CaChannel_{}".format(i), 0)
    h_cachannel= IMP.atom.Hierarchy(cachannel)
    h_cachannel_root.add_child(h_cachannel)
#print(IMP.core.RigidBody(h_cachannel_root.get_children()[0]).get_rigid_members())
# --------------------

# Define scoring functions

# --------------------
# I. Optimizer States
cavos= IMP.insulinsecretion.CaChannelOpeningOptimizerState(m, h_cachannel_root.get_children(), Oscillation, N_trough, N_peak, OscillationPeriod)

vdos=IMP.insulinsecretion.VesicleDockingOptimizerState(h_vesicles_root.get_children(), h_cachannel_root.get_children(), VDOS_CONTACT_RANGE, VDOS_SLACK, READY_STATE, VDOS_PERIOD)

isos= IMP.insulinsecretion.InsulinSecretionOptimizerState(m, h_vesicles_root.get_children(),nucleus_sphere, READY_STATE, ISOS_CUT_OFF,ISOS_PERIOD)

# I. Restraintsss
# Restraints - match score with particles:
rs = []

# Add bounding box and bounding shphere restraint
bb_harmonic= IMP.core.HarmonicUpperBound(0, K_BB)
pbc_bsss = IMP.core.BoundingSphere3DSingletonScore(bb_harmonic, pbc_sphere)
outer_bbss = IMP.core.BoundingBox3DSingletonScore(bb_harmonic, bb)
rs.append(IMP.container.SingletonsRestraint(pbc_bsss, h_vesicles_root.get_children()))
rs.append(IMP.container.SingletonsRestraint(outer_bbss, h_vesicles_root.get_children()))

# Add excluded volume restraints among all (close pairs of) particles, slack affects speed only
ev = IMP.core.ExcludedVolumeRestraint(IMP.atom.get_leaves(h_root), K_EXCLUDED, 10, "EV")
rs.append(ev)

# Add vesicle trafficking restraint
gtsc= IMP.insulinsecretion.VesicleTraffickingSingletonScore([0, 0, 0], K_TRAFFIC) # Push particles radially away or towards the center of some sphere
rs.append(IMP.container.SingletonsRestraint(gtsc,h_vesicles_root.get_children()))

# Add RDF restraints on insulin vesicles
rdfss= IMP.insulinsecretion.RadialDistributionFunctionSingletonScore(pbc_sphere, nucleus_sphere, PARAM_RDF, K_RDF)
rs.append(IMP.container.SingletonsRestraint(rdfss, h_vesicles_root.get_children()))

# Scoring Function from restraints
sf = IMP.core.RestraintsScoringFunction(rs, "SF")

# --------------------

# Define sampling parameterss

# --------------------

bd = IMP.atom.BrownianDynamics(m)
bd.set_log_level(IMP.SILENT)
bd.set_scoring_function(sf)
bd.set_maximum_time_step(bd_step_size_fs) # in femtoseconds
bd.set_temperature(310.15) #37 celsius, the temperature used in WF experiments

# -------- Add RMF visualization --------
rmf = RMF.create_rmf_file(str(condition) + '_' + str(K_TRAFFIC) + 'Ktraffic_'+ str(K_RDF) + 'Krdf_' + str(READY_STATE) + 'readystate_' + str(repeat) + 'repeat.rmf')
rmf.set_description("Brownian dynamics trajectory with {}fs timestep.\n"\
                    .format(bd_step_size_fs))
IMP.rmf.add_hierarchy(rmf, h_root)
IMP.rmf.add_restraints(rmf, rs)
IMP.rmf.add_geometry(rmf, IMP.display.BoundingBoxGeometry(bb))
IMP.rmf.add_geometry(rmf, IMP.display.SphereGeometry(pbc_sphere))

# Pair RMF with model using an OptimizerState ("listener")
sos = IMP.rmf.SaveOptimizerState(m, rmf)
sos.set_log_level(IMP.SILENT)
sos.set_simulator(bd)
sos.set_period(rmf_dump_interval_frames)
bd.add_optimizer_state(cavos)
bd.add_optimizer_state(vdos)
bd.add_optimizer_state(isos)
bd.add_optimizer_state(sos)

# Dump initial frame to RMF
sos.update_always("initial conformation")

# -------- Run simulation ---------
print("Running simulation", file = f1)
print("Score before: {:f}".format(sf.evaluate(True)), file = f1)
n_frames_left=sim_time_frames
frames_per_cycle=VDOS_PERIOD  # can be 10, or 100, dependeing on the frequency of the optimizer state and how much insulin vesicles move.
while n_frames_left>0:
    cur_n_frames=min(frames_per_cycle, n_frames_left)
    bd.optimize(cur_n_frames)
    count = []
    for i in range(0, N_VESICLES):
        count.append(IMP.insulinsecretion.SecretionCounterDecorator(h_vesicles_root.get_children()[i]).get_secretion())
    print(sim_time_frames - n_frames_left, sep=" ", file = f1)
    print(sum(count),file = f2)
    for key, values in do_stats_after_optimize(h_vesicles_root.get_children())[0].items():
        f3.write(" ".join(map(str, values)) + " ")
    f3.write("\n")
    print(*do_stats_after_optimize(h_vesicles_root.get_children())[1], sep="  ", file = f4)  #only vesicle
    print(*do_stats_after_optimize(h_vesicles_root.get_children())[2], sep="  ", file = f5)  #only vesicle
    print(*do_stats_after_optimize(h_vesicles_root.get_children())[3], sep="  ", file = f6)  #only vesicle
    n_frames_left = n_frames_left - cur_n_frames
    
print("Run finished succesfully", file = f1)
print("Score ater: {:f}".format(sf.evaluate(True)), file = f1)

end=time.time()
print('running time={} s'.format(end-start), file = f1)
