# SPDX-License-Identifier: Apache-2.0

include ../Makefile_params.common

HARNESS_ENTRY = harness
HARNESS_FILE = scalar_signed_to_unsigned_q_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = scalar_signed_to_unsigned_q

DEFINES +=
INCLUDES +=

REMOVE_FUNCTION_BODY +=
UNWINDSET +=

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c
PROJECT_SOURCES += $(SRCDIR)/mlkem/poly.c

CHECK_FUNCTION_CONTRACTS=scalar_signed_to_unsigned_q
USE_FUNCTION_CONTRACTS=ct_sel_int16 ct_cmask_neg_i16
APPLY_LOOP_CONTRACTS=on
USE_DYNAMIC_FRAMES=1

# Disable any setting of EXTERNAL_SAT_SOLVER, and choose SMT backend instead
EXTERNAL_SAT_SOLVER=
CBMCFLAGS=--smt2

# Uncomment this to see what commands litani is running...
#VERBOSE=on

# If this proof is found to consume huge amounts of RAM, you can set the
# EXPENSIVE variable. With new enough versions of the proof tools, this will
# restrict the number of EXPENSIVE CBMC jobs running at once. See the
# documentation in Makefile.common under the "Job Pools" heading for details.
# EXPENSIVE = true

# If you require access to a file-local ("static") function or object to conduct
# your proof, set the following (and do not include the original source file
# ("mlkem/poly.c") in PROJECT_SOURCES).
# REWRITTEN_SOURCES = $(PROOFDIR)/<__SOURCE_FILE_BASENAME__>.i
# include ../Makefile.common
# $(PROOFDIR)/<__SOURCE_FILE_BASENAME__>.i_SOURCE = $(SRCDIR)/mlkem/poly.c
# $(PROOFDIR)/<__SOURCE_FILE_BASENAME__>.i_FUNCTIONS = foo bar
# $(PROOFDIR)/<__SOURCE_FILE_BASENAME__>.i_OBJECTS = baz
# Care is required with variables on the left-hand side: REWRITTEN_SOURCES must
# be set before including Makefile.common, but any use of variables on the
# left-hand side requires those variables to be defined. Hence, _SOURCE,
# _FUNCTIONS, _OBJECTS is set after including Makefile.common.

include ../Makefile.common
