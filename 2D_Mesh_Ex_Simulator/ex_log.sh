NOC_WIDTH=8
NOC_HEIGHT=8
NOC_DEPTH=8

delta=0.155
point_temp=55
L_MR_passive=0.005
routing_algo=0

stp_input_file=(
./trafficnew/3d_mesh_4x4x2/fpppp_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/h264dh_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/h264dl_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/robot_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/sample_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/satell_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x4x2/sparse_3d_mesh_4x4x2.stp
./trafficnew/3d_mesh_4x8x2/fpppp_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/h264dh_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/h264dl_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/robot_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/sample_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/satell_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_4x8x2/sparse_3d_mesh_4x8x2.stp
./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp
./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp
)


./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
	${NOC_WIDTH} ${NOC_HEIGHT} ${NOC_DEPTH} 5 1 4 0 1 6 ${delta} \
	${point_temp} ${L_MR_passive} ${routing_algo}
