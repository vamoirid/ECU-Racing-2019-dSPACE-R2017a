# =============================================================================
#  Make include file Racing_2019_rti.mk:
#
#   RTI1401 7.8 (02-May-2017)
#   Sun Aug 11 09:33:09 2019
#
#   Copyright 2017, dSPACE GmbH. All rights reserved.
# =============================================================================

# Initialize variables used in blockset makefiles -----------------------------

BLOCKSET_LIBS     :=
BLOCKSET_SRCS     :=
BLOCKSET_INCLUDES :=

# Default rules for additional blocksets --------------------------------------

blockset_init          :
blockset_clean         :
blockset_deps          :
blockset_after_linkage :

# Includes for additional blocksets -------------------------------------------

%include "$(DSPACE_ROOT)\matlab\rtican\c\rtican.mk"
%include "$(DSPACE_ROOT)\Matlab\RTIUSBFlightRec\C\rtiusbflightrec.mk"


# Model-specific options ------------------------------------------------------

# Additional C source files declared by the model
MDL_CUSTOM_C_SRCS = rti_assert.c rtican_err1.c

# Additional assembler source files declared by the model
MDL_CUSTOM_ASM_SRCS =

# Additional libraries declared by the model
MDL_CUSTOM_LIBS = \
  "$(DSPACE_ROOT)\DS1401\RTPython\dsrtt1401.lib"

# Additional objects declared by the model
MDL_CUSTOM_OBJS =

# Directories where additional C and assembler source files are stored
MDL_CUSTOM_SRCS_DIR =

# Directories where additional header files are stored
MDL_CUSTOM_INCLUDES_PATH = \
  "$(DSPACE_ROOT)\DS1401\RTPython"

# Dependencies declared by the model
Racing_2019.$(OBJ_EXT) :"rtican_include.h" 

# Define build type information
BUILDTYPE = RTI

# EOF -------------------------------------------------------------------------
