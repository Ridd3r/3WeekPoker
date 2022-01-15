-makelib xcelium_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2018.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib -sv \
  "C:/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "C:/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "C:/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "C:/Xilinx/Vivado/2018.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/9097/src/mmcme2_drp.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/9097/src/axi_dynclk_S00_AXI.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/9097/src/axi_dynclk.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_dynclk_0_0/sim/hdmi_out_axi_dynclk_0_0.vhd" \
-endlib
-makelib xcelium_lib/axi_lite_ipif_v3_0_4 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/cced/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_cdc_v1_0_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/interrupt_control_v3_1_4 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/8e66/hdl/interrupt_control_v3_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_gpio_v2_0_19 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/c193/hdl/axi_gpio_v2_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_gpio_btn_0/sim/hdmi_out_axi_gpio_btn_0.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_gpio_hdmi_0/sim/hdmi_out_axi_gpio_hdmi_0.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_gpio_led_0/sim/hdmi_out_axi_gpio_led_0.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_gpio_sw_0/sim/hdmi_out_axi_gpio_sw_0.vhd" \
-endlib
-makelib xcelium_lib/lib_pkg_v1_0_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/7aff/simulation/fifo_generator_vlog_beh.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/7aff/hdl/fifo_generator_v13_2_rfs.vhd" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/7aff/hdl/fifo_generator_v13_2_rfs.v" \
-endlib
-makelib xcelium_lib/lib_fifo_v1_0_11 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/6078/hdl/lib_fifo_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/blk_mem_gen_v8_4_1 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/67d8/simulation/blk_mem_gen_v8_4.v" \
-endlib
-makelib xcelium_lib/lib_bmg_v1_0_10 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/9340/hdl/lib_bmg_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_srl_fifo_v1_0_2 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_datamover_v5_1_19 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/ec8a/hdl/axi_datamover_v5_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_vdma_v6_3_5 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/b37e/hdl/axi_vdma_v6_3_rfs.v" \
-endlib
-makelib xcelium_lib/axi_vdma_v6_3_5 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/b37e/hdl/axi_vdma_v6_3_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_axi_vdma_0_0/sim/hdmi_out_axi_vdma_0_0.vhd" \
-endlib
-makelib xcelium_lib/axis_infrastructure_v1_1_0 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/0ab1/hdl/axis_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axis_register_slice_v1_1_17 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/15d7/hdl/axis_register_slice_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tdata_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tuser_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tstrb_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tkeep_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tid_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tdest_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/tlast_hdmi_out_axis_subset_converter_0_0.v" \
-endlib
-makelib xcelium_lib/axis_subset_converter_v1_1_17 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/5a7d/hdl/axis_subset_converter_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdl/top_hdmi_out_axis_subset_converter_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/sim/hdmi_out_axis_subset_converter_0_0.v" \
-endlib
-makelib xcelium_lib/proc_sys_reset_v5_0_12 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/f86a/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_proc_sys_reset_0_0/sim/hdmi_out_proc_sys_reset_0_0.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_proc_sys_reset_1_0/sim/hdmi_out_proc_sys_reset_1_0.vhd" \
-endlib
-makelib xcelium_lib/axi_infrastructure_v1_1_0 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/smartconnect_v1_0 -sv \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/5bb9/hdl/sc_util_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/axi_protocol_checker_v2_0_3 -sv \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/03a9/hdl/axi_protocol_checker_v2_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/axi_vip_v1_1_3 -sv \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/b9a8/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/processing_system7_vip_v1_0_5 -sv \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/70fd/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_processing_system7_0_0/sim/hdmi_out_processing_system7_0_0.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/ClockGen.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/SyncAsync.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/SyncAsyncReset.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/DVI_Constants.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/OutputSERDES.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/TMDS_Encoder.vhd" \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/e3fc/src/rgb2dvi.vhd" \
  "../../../bd/hdmi_out/ip/hdmi_out_rgb2dvi_0_0/sim/hdmi_out_rgb2dvi_0_0.vhd" \
-endlib
-makelib xcelium_lib/v_tc_v6_1_12 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/6694/hdl/v_tc_v6_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/v_vid_in_axi4s_v4_0_8 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/d987/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/v_axi4s_vid_out_v4_0_9 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/9a07/hdl/v_axi4s_vid_out_v4_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_v_axi4s_vid_out_0_0/sim/hdmi_out_v_axi4s_vid_out_0_0.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_v_tc_0_0/sim/hdmi_out_v_tc_0_0.vhd" \
-endlib
-makelib xcelium_lib/xlconcat_v2_1_1 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/2f66/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_xlconcat_0_0/sim/hdmi_out_xlconcat_0_0.v" \
-endlib
-makelib xcelium_lib/xlconstant_v1_1_5 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/f1c3/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_xlconstant_0_0/sim/hdmi_out_xlconstant_0_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_xlconstant_1_0/sim/hdmi_out_xlconstant_1_0.v" \
-endlib
-makelib xcelium_lib/generic_baseblocks_v2_1_0 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_register_slice_v2_1_17 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/6020/hdl/axi_register_slice_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_data_fifo_v2_1_16 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/247d/hdl/axi_data_fifo_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_crossbar_v2_1_18 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/15a3/hdl/axi_crossbar_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_xbar_0/sim/hdmi_out_xbar_0.v" \
-endlib
-makelib xcelium_lib/axi_protocol_converter_v2_1_17 \
  "../../../../hdmi-out.srcs/sources_1/bd/hdmi_out/ipshared/ccfb/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/ip/hdmi_out_auto_pc_1/sim/hdmi_out_auto_pc_1.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_s00_regslice_0/sim/hdmi_out_s00_regslice_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_s00_data_fifo_0/sim/hdmi_out_s00_data_fifo_0.v" \
  "../../../bd/hdmi_out/ip/hdmi_out_auto_pc_0/sim/hdmi_out_auto_pc_0.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/hdmi_out/sim/hdmi_out.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

