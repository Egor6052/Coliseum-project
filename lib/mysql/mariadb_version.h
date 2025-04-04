/*
 * Kluge to support multilib installation of both 32- and 64-bit RPMS:
 * we need to arrange that header files that appear in both RPMs are
 * identical.  Hence, this file is architecture-independent and calls
 * in an arch-dependent file that will appear in just one RPM.
 *
 * To avoid breaking arches not explicitly supported by Red Hat, we
 * use this indirection file *only* on known multilib arches.
 *
 * We pay attention to include _only_ the original multilib-unclean
 * header file.  Including any other system-header file could cause
 * unpredictable include-ordering issues (rhbz#1412274, comment #16).
 *
 * Note: this may well fail if user tries to use gcc's -I- option.
 * But that option is deprecated anyway.
 */
#if defined(__x86_64__)
#include "mariadb_version-x86_64.h"
#elif defined(__i386__)
#include "mariadb_version-i386.h"
#elif defined(__ppc64__) || defined(__powerpc64__)
#include "mariadb_version-ppc64.h"
#elif defined(__ppc__) || defined(__powerpc__)
#include "mariadb_version-ppc.h"
#elif defined(__s390x__)
#include "mariadb_version-s390x.h"
#elif defined(__s390__)
#include "mariadb_version-s390.h"
#elif defined(__sparc__) && defined(__arch64__)
#include "mariadb_version-sparc64.h"
#elif defined(__sparc__)
#include "mariadb_version-sparc.h"
#endif
