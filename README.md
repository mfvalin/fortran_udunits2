### fortran_udunits2
Fortran 200x interface to the libudunits2 library from Unidata<br>
(currently modeled after version 2.0.4, but should work with subsequent versions)
```
the C library libudunits2 is
  Copyright University Corporation for Atmospheric Research and contributors
this Fortran Interface is
  Copyright Université du Québec à Montréal (UQAM) 2012-2021

a version of the Fortran compiler that supports
  use ISO_C_BINDING
is needed (development/testing done originally with gfortran 4.6)
recent versions of the GNU / Portland group / Intel / IBM xlf compilers should work

recently tested with GNU Fortran, Nvidia, AOCC, Intel Fortran compilers
 GNU Fortran (GCC) 11.1.0
 AMD clang version 13.0.0 (CLANG: AOCC_3.2.0-Build#128 2021_11_12) (based on LLVM Mirror.Version.13.0.0)
 ifort (IFORT) 2021.4.0 20210910
 pgfortran (aka nvfortran) 21.11-0 64-bit target on x86-64 Linux

for all the C functions that have been interfaced:

0-  the calling FORTRAN code must include
          use f_udunits_2
          to use these FORTRAN functions/subroutines

1-  the FORTRAN name will be the C name prefixed with f_
    FORTRAN function f_ut_read_xml mimics C function ut_read_xml

2-  where the C code uses a typed pointer, the FORTRAN code uses a typed object

    type(UT_SYSTEM_PTR)     replaces ut_system*
    type(UT_UNIT_PTR)       replaces ut_unit*
    type(CV_CONVERTER_PTR)  replaces cv_converter*

3-  where a C function has a void return, a FORTRAN subroutine is used

4-  where a C function returns zero/nonzero for a C style true/false
    the equivalent FORTRAN function returns a FORTRAN logical
      (to be usable in an equivalent way in a logical expression)

5a- where a C input argument is char *, the FORTRAN code uses character(len=*)
    copy to a C compatible zero terminated string is handled internally
      the FORTRAN string is "trailing blanks trimmed" before the zero byte is added

5b- where a C function returns char *, the FORTRAN function return type is character(len=256)

6-  ut_status is an integer, symbols with the same name are available to FORTRAN with
      use f_udunits_2

7-  ut_encoding is an integer, symbols with the same name are available to FORTRAN with
      use f_udunits_2

NOTES:

FORTRAN interface(s) for function(s) returning char * (ut_trim) not implemented
one should use the FORTRAN trim function (may not work in all cases)

FORTRAN interfaces to "visitor" functions are not implemented
      ut_accept_visitor (const ut_unit* unit, const ut_visitor* visitor, void* arg)
      Data type: ut_visitor 

FORTRAN interfaces to functions using a variable argument list and message handler 
are not implemented
   int ut_handle_error_message (const char* fmt, ...)
   ut_error_message_handler ut_set_error_message_handler (ut_error_message_handler handler)
   int ut_write_to_stderr (const char* fmt, va_list args)
   int ut_ignore (const char* fmt, va_list args)
   int ut_ignore (const char* fmt, va_list args)
   typedef int (*ut_error_message_handler)(const char* fmt, va_list args);
```
see C API documentation https://www.unidata.ucar.edu/software/udunits/udunits-2.0.4/udunits2lib.html
