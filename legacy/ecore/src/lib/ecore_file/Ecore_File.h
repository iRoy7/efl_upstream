#ifndef ECORE_FILE_H
#define ECORE_FILE_H

/*
 * TODO:
 * - More events, move/rename of directory file
 */

#include <Eina.h>

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ECORE_FILE_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif /* ! DLL_EXPORT */
# else
#  define EAPI __declspec(dllimport)
# endif /* ! EFL_ECORE_FILE_BUILD */
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

/**
 * @file Ecore_File.h
 * @brief Files utility functions
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Ecore_File_Monitor       Ecore_File_Monitor;
typedef struct _Ecore_File_Monitor_Event Ecore_File_Monitor_Event;
typedef struct _Ecore_File_Download_Job  Ecore_File_Download_Job;

typedef enum
{
   ECORE_FILE_EVENT_NONE,
   ECORE_FILE_EVENT_CREATED_FILE,
   ECORE_FILE_EVENT_CREATED_DIRECTORY,
   ECORE_FILE_EVENT_DELETED_FILE,
   ECORE_FILE_EVENT_DELETED_DIRECTORY,
   ECORE_FILE_EVENT_DELETED_SELF,
   ECORE_FILE_EVENT_MODIFIED
} Ecore_File_Event;

/* File operations */

EAPI int            ecore_file_init         (void);
EAPI int            ecore_file_shutdown     (void);
EAPI long long      ecore_file_mod_time     (const char *file);
EAPI long long      ecore_file_size         (const char *file);
EAPI Eina_Bool      ecore_file_exists       (const char *file);
EAPI Eina_Bool      ecore_file_is_dir       (const char *file);
EAPI Eina_Bool      ecore_file_mkdir        (const char *dir);
EAPI int            ecore_file_mkdirs       (const char **dirs);
EAPI int            ecore_file_mksubdirs    (const char *base, const char **subdirs);
EAPI Eina_Bool      ecore_file_rmdir        (const char *dir);
EAPI Eina_Bool      ecore_file_recursive_rm (const char *dir);
EAPI Eina_Bool      ecore_file_mkpath       (const char *path);
EAPI int            ecore_file_mkpaths      (const char **paths);
EAPI Eina_Bool      ecore_file_cp           (const char *src, const char *dst);
EAPI Eina_Bool      ecore_file_mv           (const char *src, const char *dst);
EAPI Eina_Bool      ecore_file_symlink      (const char *src, const char *dest);
EAPI char          *ecore_file_realpath     (const char *file);
EAPI Eina_Bool      ecore_file_unlink       (const char *file);
EAPI Eina_Bool      ecore_file_remove       (const char *file);
EAPI const char    *ecore_file_file_get     (const char *path);
EAPI char          *ecore_file_dir_get      (const char *path);
EAPI Eina_Bool      ecore_file_can_read     (const char *file);
EAPI Eina_Bool      ecore_file_can_write    (const char *file);
EAPI Eina_Bool      ecore_file_can_exec     (const char *file);
EAPI char          *ecore_file_readlink     (const char *link);
EAPI Eina_List     *ecore_file_ls           (const char *dir);
EAPI Eina_Iterator *ecore_file_ls_iterator  (const char *dir);
EAPI char          *ecore_file_app_exe_get  (const char *app);
EAPI char          *ecore_file_escape_name  (const char *filename);
EAPI char          *ecore_file_strip_ext    (const char *file);
EAPI int            ecore_file_dir_is_empty (const char *dir);

/* Monitoring */

EAPI Ecore_File_Monitor *ecore_file_monitor_add(const char *path,
                                                void (*func) (void *data,
                                                              Ecore_File_Monitor *em,
                                                              Ecore_File_Event event,
                                                              const char *path),
                                                void *data);
EAPI void                ecore_file_monitor_del(Ecore_File_Monitor *ecore_file_monitor);
EAPI const char         *ecore_file_monitor_path_get(Ecore_File_Monitor *ecore_file_monitor);

/* Path */

EAPI Eina_Bool  ecore_file_path_dir_exists(const char *in_dir);
EAPI Eina_Bool  ecore_file_app_installed(const char *exe);
EAPI Eina_List *ecore_file_app_list(void);

/* Download */

EAPI Eina_Bool ecore_file_download(const char *url,
                              const char *dst, 
                              void (*completion_cb)(void *data,
                                                    const char *file,
                                                    int status),
                              int (*progress_cb)(void *data,
                                                 const char *file,
                                                 long int dltotal,
                                                 long int dlnow,
                                                 long int ultotal,
                                                 long int ulnow),
                              void *data, 
                              Ecore_File_Download_Job **job_ret);
EAPI void ecore_file_download_abort_all(void);  
EAPI void ecore_file_download_abort(Ecore_File_Download_Job *job);
EAPI Eina_Bool ecore_file_download_protocol_available(const char *protocol);

#ifdef __cplusplus
}
#endif

#endif
