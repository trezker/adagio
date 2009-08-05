import glob
import sys
import os

files = glob.glob('src/*.cpp')
files = [x.replace("src", "obj") for x in files]

env = Environment(CPPPATH = ['include'])

debug = ARGUMENTS.get('debug', 0)
if int(debug):
	env.Append(CCFLAGS = '-g')
env.Append(CCFLAGS = '-Wall')

env.BuildDir('obj','src', duplicate = 0)
env.Append(LIBS=['allegro-4.9.13','a5_iio-4.9.13','a5_font-4.9.13','a5_ttf-4.9.13','a5_primitives-4.9.13','kcm_audio-4.9.13','a5_vorbis-4.9.13'])
adagio = env.StaticLibrary('lib/adagio',files)
adagio_shared = env.SharedLibrary('lib/adagio',files)

#env.Append(LIBS = [adagio])
#test_exe = env.Program('test/test', 'test/test.c')

##### Install #####
env.Alias('install', '/usr/local')
env.Install('/usr/local/lib', adagio)
env.Install('/usr/local/lib', adagio_shared)
include_files = glob.glob('include/adagio/*.h')
env.Install('/usr/local/include/adagio', include_files)


rebuild_docs = ARGUMENTS.get('rebuild_docs', 0)
if int(rebuild_docs):
	os.system("../NaturalDocs/NaturalDocs -i include -i docs/nd -o HTML docs/html -p nd -ro")
else:
	os.system("../NaturalDocs/NaturalDocs -i include -i docs/nd -o HTML docs/html -p nd")
	
##### Unit tests #####
#def runUnitTest(env,target,source):
#	os.system("cp lib/liballua.so test/liballua.so")
#	os.system("cd test && lua unittest_main.lua")

#Command("test.passed",'test',runUnitTest)
