!    Fortran interface to the C library libudunits2
!    (currently modeled after version 2.0.4, but should work with subsequent versions)
!        the C library libudunits2 is
!            Copyright University Corporation for Atmospheric Research and contributors
!        this fortran Interface is is
!            Copyright Université du Québec à Montréal (UQAM) 2012-2021
!        see LICENSE file in repository (BSD 3-Clause License)
!
! documentation for c code :
! http://www.unidata.ucar.edu/software/udunits/udunits-2.0.4/udunits2lib.html
        type, bind(C) :: UT_SYSTEM_PTR
           type(C_PTR) :: ptr
        end type
        type(UT_SYSTEM_PTR), parameter :: UT_SYSTEM_PTR_NULL = UT_SYSTEM_PTR(C_NULL_PTR)

        type, bind(C) :: UT_UNIT_PTR
           type(C_PTR) :: ptr
        end type
        type(UT_UNIT_PTR), parameter ::UT_UNIT_PTR_NULL = UT_UNIT_PTR(C_NULL_PTR)

        type, bind(C) :: CV_CONVERTER_PTR
           type(C_PTR) :: ptr
        end type
        type(CV_CONVERTER_PTR), parameter ::CV_CONVERTER_PTR_NULL = CV_CONVERTER_PTR(C_NULL_PTR)

        type, bind(C) :: UT_STATUS
           integer(C_INT) :: value
        end type

        type :: CHAR_STAR
           character(len=1), dimension(:), pointer :: ptr
        end type
        type(CHAR_STAR), parameter ::CHAR_STAR_NULL = CHAR_STAR(NULL())
!
!   the following constants are lifted from C enum in udunits2.h
!   and may have to be adjusted should any change be made to that file
!
!   a cleaner way would be to use a C program to produce this file
!
        integer, parameter :: UT_ASCII = 0
        integer, parameter :: UT_ISO_8859_1 = 1
        integer, parameter :: UT_LATIN1 = UT_ISO_8859_1
        integer, parameter :: UT_UTF8 = 2

        integer, parameter :: UT_NAMES = 4
        integer, parameter :: UT_DEFINITION = 8

        integer, parameter :: UT_SUCCESS = 0
        integer, parameter :: UT_BAD_ARG = 1
        integer, parameter :: UT_EXISTS = 2
        integer, parameter :: UT_NO_UNIT = 3
        integer, parameter :: UT_OS = 4
        integer, parameter :: UT_NOT_SAME_SYSTEM = 5
        integer, parameter :: UT_MEANINGLESS = 6
        integer, parameter :: UT_NO_SECOND = 7
        integer, parameter :: UT_VISIT_ERROR = 8
        integer, parameter :: UT_CANT_FORMAT = 9
        integer, parameter :: UT_SYNTAX = 10
        integer, parameter :: UT_UNKNOWN = 11
        integer, parameter :: UT_OPEN_ARG = 12
        integer, parameter :: UT_OPEN_ENV = 13
        integer, parameter :: UT_OPEN_DEFAULT = 14
        integer, parameter :: UT_PARSE = 15
