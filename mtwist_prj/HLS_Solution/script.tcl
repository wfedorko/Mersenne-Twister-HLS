############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project mtwist_prj
set_top mtwist_core
add_files rand.dat
add_files sources/mtwist.cpp
add_files -tb sources/mtwist_tb.cpp
open_solution "HLS_Solution"
set_part {xc7vx690tffg1761-2}
create_clock -period 2.00 -name default
set_clock_uncertainty 0
#source "./mtwist_prj/HLS_Solution/directives.tcl"
csim_design -clean
csynth_design
cosim_design -compiler gcc -rtl vhdl
export_design -format ip_catalog
