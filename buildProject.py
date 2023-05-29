# Short script to build project on any platform.
# Still, you will need to have installed CMake and Conan2.0.

import subprocess

commands =  ['conan install . --build=missing --output-folder=build',
            'conan install . --build=missing --output-folder=build -s build_type=Debug',
            'cd build',
            'cmake --preset conan-default',
            'cmake --build --preset conan-debug',
            'cmake --build --preset conan-release']

for command in commands:
    subprocess.run(command, shell=True)
