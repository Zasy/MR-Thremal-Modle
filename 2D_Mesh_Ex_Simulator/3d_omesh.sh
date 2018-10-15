 #!/bin/sh

stp_input_file=(
./trafficnew/2d_mesh_4x4x2/fpppp_3d_mesh_4x4x2.stp
./trafficnew/2d_mesh_4x4x2/h264dh_3d_mesh_4x4x2.stp
./trafficnew/2d_mesh_4x4x2/h264dl_3d_mesh_4x4x2.stp
./trafficnew/2d_mesh_4x4x2/robot_3d_mesh_4x4x2.stp
./trafficnew/2d_mesh_4x4x2/sample_3d_mesh_4x4x2.stp
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


i=14
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 1		
i=15
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 16
i=16
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 8
i=17
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 8
i=18
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 16
i=19
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 1
i=20
./3D_OMESH ${stp_input_file[$i]}  8 8 2 5 2 4 0 16	
