root_include_dir    := include
root_source_dir    := src
source_subdirs    := . classes
compile_flags      := -Wall -MD -pipe
link_flags            := -s -pipe
libraries               := -ldl
 
relative_include_dirs   := $(addprefix ../../, $(root_include_dir))
relative_source_dirs   := $(addprefix ../../$(root_source_dir)/, $(source_subdirs))
objects_dirs               := $(addprefix $(root_source_dir)/, $(source_subdirs))
objects                      := $(patsubst ../../%, %, $(wildcard $(addsuffix /*.c*, $(relative_source_dirs))))
objects                      := $(objects:.cpp=.o)
objects                      := $(objects:.c=.o)
 
all : $(program_name)
 
$(program_name) : obj_dirs $(objects)
	g++ -o $@ $(objects) $(link_flags) $(libraries)
 
obj_dirs :
	mkdir -p $(objects_dirs)
 
VPATH := ../../
 
%.o : %.cpp
	g++ -g -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
 
%.o : %.c
	g++ -o $@ -c $< $(compile_flags) $(build_flags) $(addprefix -I, $(relative_include_dirs))
 
.PHONY : clean
 
clean :
	rm -rf bin obj
 
include $(wildcard $(addsuffix /*.d, $(objects_dirs)))
