Import('*')

import yadeSCons
yadeSCons.buildPluginLibs(env,env['buildPlugs'])
SConscript(dirs=['core','lib']+[d for d in ('extra','py','gui') if d not in env['exclude']],duplicate=0)
