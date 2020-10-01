###################################################
# LIBRARY SOURCES
###################################################

# Set mylib folder path.
# IMPORTANT NOTE: change MYLIBTEMPLATE_PATH to your Driver name e.g. JOYSTICK_MYLIBPATH
# e.g. JOYSTICK_MYLIBPATH=/home/csse3010/mylib/joystick
PROJECT_PATH=/home/csse3010/csse3010/mylib/project

# Set folder path with header files to include.
CFLAGS += -I$(PROJECT_PATH)

# List all c files locations that must be included (use space as separate e.g. LIBSRCS += path_to/file1.c path_to/file2.c)
LIBSRCS += $(PROJECT_PATH)/s4464952_CAG_Display.c $(PROJECT_PATH)/s4464952_CAG_Joystick.c $(PROJECT_PATH)/s4464952_CAG_keypad_grid.c $(PROJECT_PATH)/s4464952_CAG_keypad_mnemonic.c $(PROJECT_PATH)/s4464952_CAG_Simulator.c


