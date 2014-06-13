# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'
$CFLAGS << " -std=c++0x -pthread";
have_library('stdc++')
create_makefile('socker_in_c/socker_in_c')
