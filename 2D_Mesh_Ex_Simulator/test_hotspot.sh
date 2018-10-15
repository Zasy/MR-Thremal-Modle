NOC_WIDTH=8
NOC_HEIGHT=8
NOC_DEPTH=2

delta=0.155
point_temp=55
L_MR_passive=0.005
routing_logo=0

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &


delta=0.155
point_temp=55
L_MR_passive=0.005
routing_logo=1

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &

delta=0.155
point_temp=55
L_MR_passive=0.005
routing_logo=2

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &


delta=0.155
point_temp=55
L_MR_passive=0.005
routing_logo=3

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &



delta=0.31
point_temp=55
L_MR_passive=0.005
routing_logo=0

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &


delta=0.31
point_temp=55
L_MR_passive=0.005
routing_logo=1

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &

delta=0.31
point_temp=55
L_MR_passive=0.005
routing_logo=2

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &


delta=0.31
point_temp=55
L_MR_passive=0.005
routing_logo=3

./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sample_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 5 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/satell_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 3 ${delta} ${point_temp} ${L_MR_passsive}&
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/robot_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 0 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/sparse_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 1 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dl_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 8 2 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/h264dh_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 16 4 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
./3D_OMESH ./trafficnew/3d_mesh_8x8x2/fpppp_3d_mesh_8x8x2.stp \
    8 8 2 20 2 18 0 1 6 ${delta} ${point_temp} ${L_MR_passive} \
    ${routing_algo} &
