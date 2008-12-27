import os

opts = Options('')
opts.Add(EnumOption('build', 'Build configuration', 'release', allowed_values=('debug', 'release')))
opts.Add(EnumOption('arch', 'Release optimization Pentium Pro', 'native', allowed_values=('native', 'ppro')))
opts.Add(BoolOption('static', 'Set to build staticaly-linked binary', 0))

env = Environment()

env.Replace(CCFLAGS = '-O2 -Wall --omit-frame-pointer -pipe')

Export('env')

SConscript(['rtsp_sdk/SConscript', 'sdp/SConscript'])
#SConscript('rtsp_sdk/SConscript')

