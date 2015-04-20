/**
 * @file Elua.h
 * @brief Elua Library
 *
 * @defgroup Elua Elua
 */

/**
 *
 * @section intro Elua library
 *
 * The Elua library was created to ease integration of EFL Lua into other EFL
 * libraries or applications. Using the Elua library you can easily create a
 * Lua state that is fully set up for running EFL Lua bindings.
 *
 * You can find the API documentation at @ref Elua
*/
#ifndef _ELUA_H
#define _ELUA_H

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ELUA_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif /* ! DLL_EXPORT */
# else
#  define EAPI __declspec(dllimport)
# endif /* ! EFL_ELUA_BUILD */
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif /* ! _WIN32 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

/**
 * @page elua_main Elua library (BETA)
 *
 * @date 2015 (created)
 *
 * @section toc Table of Contents
 *
 * @li @ref elua_main_intro
 * @li @ref elua_main_compiling
 * @li @ref elua_main_next_steps
 *
 * @section elua_main_intro Introduction
 *
 * The Elua library provides all necessary infrastructure required to set up
 * a fully functional Lua state able of running Elua scripts. This is provided
 * as a library in order to encourage reuse from different libraries and apps.
 *
 * @section elua_main_compiling How to compile
 *
 * As Elua is a library, compiling is very simple.
 *
 * Compiling C or C++ files into object files:
 *
 * @verbatim
   gcc -c -o main.o main.c `pkg-config --cflags elua`
   @endverbatim
 *
 * Linking object files into a binary executable:
 *
 * @verbatim
   gcc -o my_application main.o `pkg-config --libs elua`
   @endverbatim
 *
 * See @ref pkgconfig
 *
 * @section elua_main_next_steps Next Steps
 *
 * There is a comperehensive API reference available that should get you up
 * and running.
 *
 * @addtogroup Elua
 * @{
 */

#ifdef EFL_BETA_API_SUPPORT

#include <Eina.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

typedef struct _Elua_State Elua_State;

EAPI int elua_init(void);
EAPI int elua_shutdown(void);

EAPI Elua_State *elua_state_new(const char *progname);
EAPI Elua_State *elua_state_from_lua_state_get(lua_State *L);

EAPI void elua_state_free(Elua_State *es);

EAPI void elua_state_dirs_set(Elua_State *es, const char *core,
                              const char *mods, const char *apps);
EAPI void elua_state_dirs_fill(Elua_State *es, Eina_Bool ignore_env);

EAPI Eina_Stringshare *elua_state_core_dir_get(const Elua_State *es);
EAPI Eina_Stringshare *elua_state_mod_dir_get(const Elua_State *es);
EAPI Eina_Stringshare *elua_state_apps_dir_get(const Elua_State *es);

EAPI Eina_Stringshare *elua_state_prog_name_get(const Elua_State *es);

EAPI void elua_state_include_path_add(Elua_State *es, const char *path);

EAPI Eina_Bool elua_state_require_ref_push(Elua_State *es);
EAPI Eina_Bool elua_state_appload_ref_push(Elua_State *es);

EAPI lua_State *elua_state_lua_state_get(const Elua_State *es);

EAPI Eina_Bool elua_state_i18n_setup(const Elua_State *es);
EAPI Eina_Bool elua_state_modules_setup(const Elua_State *es);
EAPI Eina_Bool elua_state_io_setup(const Elua_State *es);

EAPI int elua_io_loadfile(const Elua_State *es, const char *fname);

EAPI int elua_util_require(Elua_State *es, const char *libname);
EAPI int elua_util_file_run(Elua_State *es, const char *fname);
EAPI int elua_util_string_run(Elua_State *es, const char *chunk,
                              const char *chname);
EAPI Eina_Bool elua_util_app_load(Elua_State *es, const char *appname);
EAPI int elua_util_script_run(Elua_State *es, int argc, char **argv, int n,
                              int *quit);

EAPI int elua_util_error_report(const Elua_State *es, const char *pname,
                                int status);

#endif

#ifdef __cplusplus
} // extern "C" {
#endif

#endif
