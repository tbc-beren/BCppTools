/**
*  \file    bcpptools/core/bcerror.h
*  \brief   Generic error related stuff such as error categories and error codes
*/
#ifndef __bctools__error__
#define __bctools__error__


#include <bcpptools/core/bctypes.h>


#ifdef __cplusplus
extern "C"
{
#endif


typedef uint32_t                    bcerror_t;


#define bcerrorarea_generic         0x00000000
#define bcerrorarea_bcaplib         0x00010000
#define bcerrorarea_custom_app      0x40000000


#define bcerror_ok                  (bcerrorarea_generic|0x0000)
#define bcerror_generic             (bcerrorarea_generic|0x0001)
#define bcerror_not_implemented     (bcerrorarea_generic|0x0002)
#define bcerror_not_supported       (bcerrorarea_generic|0x0003)
#define bcerror_unexpected          (bcerrorarea_generic|0x0004)
#define bcerror_invalid_param       (bcerrorarea_generic|0x0005)
#define bcerror_out_of_memory       (bcerrorarea_generic|0x0006)
#define bcerror_pending             (bcerrorarea_generic|0x0007)
#define bcerror_open_failed         (bcerrorarea_generic|0x0008)
#define bcerror_create_failed       (bcerrorarea_generic|0x0009)
#define bcerror_read_failed         (bcerrorarea_generic|0x000A)
#define bcerror_write_failed        (bcerrorarea_generic|0x000B)
#define bcerror_not_connected       (bcerrorarea_generic|0x000C)
#define bcerror_invalid             (bcerrorarea_generic|0x000D)
#define bcerror_invalid_state       (bcerrorarea_generic|0x000E)
#define bcerror_invalid_file        (bcerrorarea_generic|0x000F)
#define bcerror_eof                 (bcerrorarea_generic|0x0010)
#define bcerror_overflow            (bcerrorarea_generic|0x0011)
#define bcerror_buffer_overflow     bcerror_overflow
#define bcerror_not_found           (bcerrorarea_generic|0x0012)
#define bcerror_missing_component   (bcerrorarea_generic|0x0013)
#define bcerror_self_test_failed    (bcerrorarea_generic|0x0014)
#define bcerror_access_denied       (bcerrorarea_generic|0x0015)


#ifdef __cplusplus
} // extern "C"
#endif


#endif // __bctools__error__
