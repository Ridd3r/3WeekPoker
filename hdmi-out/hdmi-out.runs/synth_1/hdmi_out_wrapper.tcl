# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7z010clg400-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.cache/wt [current_project]
set_property parent.project_path C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property board_part digilentinc.com:zybo:part0:1.0 [current_project]
set_property ip_repo_paths {
  c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.ipdefs/repo_0_0
  c:/Users/suhai/Desktop/digitale_systemer/vivado/NotIP
} [current_project]
set_property ip_output_repo c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/imports/hdl/hdmi_out_wrapper.vhd
add_files C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/hdmi_out.bd
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_btn_0/hdmi_out_axi_gpio_btn_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_btn_0/hdmi_out_axi_gpio_btn_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_btn_0/hdmi_out_axi_gpio_btn_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_hdmi_0/hdmi_out_axi_gpio_hdmi_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_hdmi_0/hdmi_out_axi_gpio_hdmi_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_hdmi_0/hdmi_out_axi_gpio_hdmi_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_led_0/hdmi_out_axi_gpio_led_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_led_0/hdmi_out_axi_gpio_led_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_led_0/hdmi_out_axi_gpio_led_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_sw_0/hdmi_out_axi_gpio_sw_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_sw_0/hdmi_out_axi_gpio_sw_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_sw_0/hdmi_out_axi_gpio_sw_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_vdma_0_0/hdmi_out_axi_vdma_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_vdma_0_0/hdmi_out_axi_vdma_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_vdma_0_0/hdmi_out_axi_vdma_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axis_subset_converter_0_0/hdmi_out_axis_subset_converter_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_proc_sys_reset_0_0/hdmi_out_proc_sys_reset_0_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_proc_sys_reset_0_0/hdmi_out_proc_sys_reset_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_proc_sys_reset_1_0/hdmi_out_proc_sys_reset_1_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_proc_sys_reset_1_0/hdmi_out_proc_sys_reset_1_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_processing_system7_0_0/hdmi_out_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_rgb2dvi_0_0/src/rgb2dvi.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_rgb2dvi_0_0/src/rgb2dvi_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_rgb2dvi_0_0/src/rgb2dvi_clocks.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_v_axi4s_vid_out_0_0/hdmi_out_v_axi4s_vid_out_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_v_axi4s_vid_out_0_0/hdmi_out_v_axi4s_vid_out_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_v_tc_0_0/hdmi_out_v_tc_0_0_clocks.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_v_tc_0_0/hdmi_out_v_tc_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_timer_0_0/hdmi_out_axi_timer_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_timer_0_0/hdmi_out_axi_timer_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_0_0/hdmi_out_axi_gpio_0_0_board.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_0_0/hdmi_out_axi_gpio_0_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_axi_gpio_0_0/hdmi_out_axi_gpio_0_0.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_auto_pc_1/hdmi_out_auto_pc_1_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_s00_regslice_0/hdmi_out_s00_regslice_0_clocks.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_s00_data_fifo_0/hdmi_out_s00_data_fifo_0_ooc.xdc]
set_property used_in_implementation false [get_files -all c:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/ip/hdmi_out_auto_pc_0/hdmi_out_auto_pc_0_ooc.xdc]
set_property used_in_implementation false [get_files -all C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/sources_1/bd/hdmi_out/hdmi_out_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/constrs_1/imports/constraints/ZYBO_Master.xdc
set_property used_in_implementation false [get_files C:/Users/suhai/Desktop/3-ugersHardware/hdmi-out/hdmi-out.srcs/constrs_1/imports/constraints/ZYBO_Master.xdc]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 0
close [open __synthesis_is_running__ w]

synth_design -top hdmi_out_wrapper -part xc7z010clg400-1 -flatten_hierarchy none -directive RuntimeOptimized -fsm_extraction off


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef hdmi_out_wrapper.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file hdmi_out_wrapper_utilization_synth.rpt -pb hdmi_out_wrapper_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
