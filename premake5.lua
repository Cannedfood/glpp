workspace 'glpp'

language   'C++'
cppdialect 'C++17'

configurations {
	'dev',
	'debug',
	'release',
}

filter 'configurations:release or dev'
	optimize 'Speed'
filter 'configurations:dev or debug'
	symbols 'On'
filter 'configurations:debug'
	optimize 'Debug'
filter 'configurations:release'
	flags 'LinkTimeOptimization'
filter {}

filter { 'configurations:dev or debug', 'toolset:gcc or clang' }
	buildoptions { '-Wall', '-Wextra', '-Wno-unused-parameter' }
filter {}

flags { 'MultiProcessorCompile', 'NoIncrementalLink' }
vectorextensions 'SSE2'
floatingpoint 'Fast'

includedirs '.'

project 'glpp'
	kind 'StaticLib'
	files 'glpp/*.cpp'

project 'example'
	kind 'ConsoleApp'
	files 'example/**'
	defines 'GLPP_NO_INLINE'
	links { 'glpp', 'GLEW', 'GL', 'glfw' }