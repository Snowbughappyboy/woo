from woo.core import *
from woo.dem import *
from woo.fem import *
import woo
import woo.gl
import math
from math import pi
from minieigen import *
woo.master.usesApi=10103

S=woo.master.scene=Scene(fields=[DemField(gravity=(0,0,0))])
S.gl.demField.nodes=True
S.gl.node.wd=4
S.gl.membrane.node=False
S.gl.node.len=.05
S.gl.membrane.phiScale=0.
S.gl.demField.glyph=woo.gl.Gl1_DemField.glyphForce

import woo.dem
# print sorted(woo.dem.__dict__.keys())

if 0:
    nn=[Node(pos=(0,0,1)),Node(pos=(0,1,1)),Node(pos=(0,1,0))]
    for n in nn:
        n.dem=DemData(inertia=(1,1,1))
        n.dem.blocked='xyz'
        rotvec=Vector3.Random()
        n.ori=Quaternion(rotvec.norm(),rotvec.normalized())
        n.dem.mass=1
    nn[2].dem.vel=(0,0,0)
    nn[2].dem.blocked=''

    S.dem.gravity=(0,0,-10)
    S.dem.par.add(Particle(shape=Membrane(nodes=nn),material=FrictMat(young=1e6)),nodes=True)
    for n in nn: n.dem.addParRef(S.dem.par[-1])
    ff=S.dem.par[0].shape
    ff.setRefConf() #update()
    S.engines=[Leapfrog(reset=True),IntraForce([In2_Membrane_ElastMat(thickness=.01,bending=False)])]
    S.dt=1e-5
    S.saveTmp()
    S.one()
    # print S.dem.par[0].shape.KK
else:
    # see http://www.youtube.com/watch?v=jimWu0_8oLc
    S.gl.demField.nodes=False
    S.gl.membrane.uScale=0.
    S.gl.membrane.relPhi=0.
    S.dem.gravity=(0,0,-30)
    S.gl.demField.colorBy='vel'
    import woo.pack, woo.utils, numpy
    xmax,ymax=1,1
    xdiv,ydiv=20,20
    ff=woo.pack.gtsSurface2Facets(woo.pack.sweptPolylines2gtsSurface([[(x,y,0) for x in numpy.linspace(0,xmax,num=xdiv)] for y in numpy.linspace(0,ymax,num=ydiv)]),flex=True)
    S.dem.par.add(ff,nodes=True)
    for n in S.dem.nodes:
        n.dem.inertia=(1.,1.,1.)
        n.dem.blocked=''
        if n.pos[0] in (0,xmax) or n.pos[1] in (0,ymax): n.dem.blocked='xyzXYZ'
        n.dem.mass=5.
    # this would be enough without spheres
    #S.engines=[Leapfrog(reset=True,damping=.05),IntraForce([In2_Membrane_ElastMat(thickness=.01)])]
    S.engines=[
        Leapfrog(reset=True,damping=.1),
        InsertionSortCollider([Bo1_Sphere_Aabb(),Bo1_Facet_Aabb()],verletDist=0.01),
        ContactLoop([Cg2_Sphere_Sphere_L6Geom(),Cg2_Facet_Sphere_L6Geom()],[Cp2_FrictMat_FrictPhys()],[Law2_L6Geom_FrictPhys_IdealElPl()],applyForces=False), # forces are applied in IntraForce
        IntraForce([In2_Membrane_ElastMat(thickness=.01,bending=False,bendThickness=.2),In2_Sphere_ElastMat()]),
        # VtkExport(out='/tmp/membrane',stepPeriod=100,what=VtkExport.spheres|VtkExport.mesh)
    ]
    
    # a few spheres falling onto the mesh
    if 1:
        sp=woo.pack.SpherePack()
        sp.makeCloud((.3,.3,.1),(.7,.7,.3),rMean=.3*xmax/xdiv,rRelFuzz=.3,periodic=False)
        sp.toSimulation(S,mat=FrictMat(young=1e6,density=3000))

    S.dt=min(1e-4,.7*woo.utils.pWaveDt(S))

    S.saveTmp()

import woo.qt
woo.qt.Controller()
woo.qt.View()
