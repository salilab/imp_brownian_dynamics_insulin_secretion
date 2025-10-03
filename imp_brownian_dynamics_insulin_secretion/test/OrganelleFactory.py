"""
Factory for generating organelles
"""

from __future__ import print_function, division
import IMP.atom
import IMP.algebra
import IMP.core
import IMP.display

class VesicleFactory:
    '''
    A class for generating insulin vesicles
    '''
    def __init__(self, model, default_R, v):
        self.model= model
        self.default_R= default_R
        self.v= v

    def _create_vesicle_core(self, name):
        '''
        Create a vesicle in model m with name "Vesicle_i"
        and radius R at a random position in the cytoplasm
        (within cell_sphere and outside ne_sphere)
        '''
        p= IMP.Particle(self.model, name)
        xyzr= IMP.core.XYZR.setup_particle(p)
        xyzr.set_coordinates_are_optimized(True)
        xyzr.set_coordinates(self.v)
        xyzr.set_radius(self.default_R)
        # Setup (fake) mass and hierearchy
        IMP.atom.Mass.setup_particle(p, 1)
        # set the coordinate values
        IMP.atom.Hierarchy.setup_particle(p) 
        IMP.display.Colored.setup_particle(p,
                                           IMP.display.get_display_color(0))
        return p

    def create_simple_vesicle(self, name):
        '''
        Create a simple granule with specified name - just a diffusive
        sphere decorated with mass, color and hierarchy
        '''
        p= self._create_vesicle_core(name)
        IMP.atom.Diffusion.setup_particle(p)
        return p

    def create_vesicle(self, name):
        '''
        Create a vesicle with a specified name and several decorators
        '''
        p= self._create_vesicle_core(name)
        IMP.atom.Diffusion.setup_particle(p)
        # Setup the decorator for counting the number of secretion events
        IMP.insulinsecretion.SecretionCounterDecorator.setup_particle(p, 0)
        IMP.insulinsecretion.MaturationStateDecorator.setup_particle(p, 0)
        IMP.insulinsecretion.DockingStateDecorator.setup_particle(p, 0)
        return p

class CaChannelFactory:
    '''
    A class for Ca2+ channels
    '''
    def __init__(self, model, default_R, v):
        self.model= model
        self.default_R= default_R
        self.v= v

    def _create_cachannel_core(self, name):
        '''
        Create a Ca2+ channel in model m with name "CaChannel_i"
        and radius R at a random position on the cell sphere
        '''
        p= IMP.Particle(self.model, name)
        xyzr= IMP.core.XYZR.setup_particle(p)
        xyzr.set_coordinates_are_optimized(True)
        xyzr.set_coordinates(self.v)
        xyzr.set_radius(self.default_R)
        # Setup (fake) mass and hierearchy
        IMP.atom.Mass.setup_particle(p, 1)   
        IMP.atom.Hierarchy.setup_particle(p)
        return p
    
    def create_simple_cachannel(self, name):
        '''
        Create a simple Ca2+ channel with specified name - just a 
        sphere decorated with mass, color and hierarchy
        '''
        p= self._create_camd_core(name)
        return p

    def create_cachannel_with_State(self,
                                                name,
                                                channelstate):
        '''
        Create a Ca2+ channels with open/closed state
        '''
        p= self._create_cachannel_core(name)
        IMP.display.Colored.setup_particle(p,
                                           IMP.display.get_display_color(1))
        IMP.insulinsecretion.CaChannelStateDecorator.setup_particle(p, channelstate)
        # Create core particle and add as rigid body core
        h= IMP.atom.Hierarchy.setup_particle(p)
        p_cachannel_core= self._create_cachannel_core(name + "_core")
        rb= IMP.core.RigidBody.setup_particle(p,
                                              [p_cachannel_core])
        h.add_child(IMP.atom.Hierarchy(p_cachannel_core))
        rb.set_coordinates_are_optimized(True)
        return p
