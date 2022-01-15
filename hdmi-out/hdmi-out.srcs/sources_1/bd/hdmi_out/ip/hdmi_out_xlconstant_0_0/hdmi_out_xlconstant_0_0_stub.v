// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Mon Jan  3 10:28:05 2022
// Host        : LAPTOP-PO14UA94 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub {C:/Users/suhai/Desktop/3-ugers
//               hardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_xlconstant_0_0/hdmi_out_xlconstant_0_0_stub.v}
// Design      : hdmi_out_xlconstant_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "xlconstant_v1_1_5_xlconstant,Vivado 2018.2" *)
module hdmi_out_xlconstant_0_0(dout)
/* synthesis syn_black_box black_box_pad_pin="dout[0:0]" */;
  output [0:0]dout;
endmodule