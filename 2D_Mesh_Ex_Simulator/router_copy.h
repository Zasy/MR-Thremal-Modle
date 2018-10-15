#include <systemc.h>
#include "Definition.h"
#include "global_data.h"
#include "shortest11.h"
class Router : public sc_module {
public:
	SC_HAS_PROCESS(Router);

	Router(sc_module_name name=sc_gen_unique_name("Router"))
		//: sc_module(name)
	{

		SC_THREAD(receiver);
		dont_initialize();
		sensitive << clk.pos();

		SC_THREAD(sender);
		dont_initialize();
		sensitive << clk.pos();

		SC_THREAD(arbiter);
		dont_initialize();
		sensitive << clk.pos();

		// the temp storage is initialized to zero
		for (int i=0; i<port_no; i++) {
			//reg_data_in[i] = 0;
			reg_data_ready_in[i] = 0;
			//reg_data_out[i] = 0;

			//reg_tear_in[i] = 0;
			reg_tear_ready_in[i] = 0;
			//reg_tear_out[i] = 0;

			//reg_ack_in[i] = 0;
			reg_ack_ready_in[i] = 0;
			//reg_ack_out[i] = 0;

			//reg_partial_in[i] = 0;
			reg_partial_ready_in[i] = 0;
			//reg_partial_out[i] = 0;
			buffer_req_out[i]=0;
			buffer_tear_out[i]=0;
			buffer_partial_out[i]=0;
			buffer_ack_out[i]=0;
			busy[i] = 0;
			timer[i]=-1;



			input_link_output[i] = -1;
			rr_pos[i]=0;
			read[i]=0;
			write[i]=0;
		}

		ack=-1;
		des=-1;
		id = -1;
		pos_x = -1;
		pos_y = -1;
		pos_z = -1;
		rr = 0;
		//rt = 4;
		busy_in=0;
		busy_out=0;
		//cout<<"KOKOKOKOKOKO"<<endl;
        //cout<<table_direction[0][0]<<" "<<table_direction[1][0]<<" "<<table_direction[2][0]<<" "<<table_direction[3][0]<<endl;
		for(int i=0;i<PROCESSOR_NUM;i++){
			ack_flag[i]=0;
		}
	}


	void receiver() {
     while(true){
		for (int i=0; i<port_no; i++){

			if(timer[i]==0){
				if(i == TO_PROCESSOR){
						if(input_link_output[i]==-1){
							cout<<"error in cluster receiver"<<endl;
							cout<<"port "<<i<<endl;
						}
						busy[input_link_output[i]]=0;
						//cout<<"at time "<<sc_time_stamp()<<" tear down "<<endl;
						if(input_link_output[i] >= PROCESSOR_NUM){
							busy_out=0;
						}

						input_link_output[i]=-1;
				}

				else {
						if(input_link_output[i]==-1){
							cout<<"error in cluster receiver 2"<<endl;
						}

						busy[input_link_output[i]]=0;
						if(input_link_output[i] == TO_PROCESSOR){
							busy_in=0;
						}
						input_link_output[i]=-1;
				}
			}

			timer[i]=timer[i]-1;

			reg_data_ready_in[i] = data_ready_in[i];
			reg_data_in[i] = data_in[i].read();

			reg_ack_ready_in[i] = ack_ready_in[i];
			reg_ack_in[i] = ack_in[i].read();

			reg_tear_ready_in[i] = tear_ready_in[i];
			reg_tear_in[i] = tear_in[i].read();

			reg_partial_ready_in[i] = partial_ready_in[i];
			reg_partial_in[i] = partial_in[i].read();

			// store data if ready
			if (reg_data_ready_in[i] == 1) {

					request[i][write[i]]=reg_data_in[i];
					write[i]=(write[i]+1)%inputbuffersize;

			}

			if (reg_tear_ready_in[i] == 1) {
				flit_type temp_flit;
				temp_flit = reg_tear_in[i].data_flit;
				int source_id = temp_flit.src;
				int src_z = source_id / (NOC_WIDTH * NOC_HEIGHT);
				int src_y = (source_id - src_z*(NOC_WIDTH * NOC_HEIGHT)) / NOC_WIDTH;
				int src_x = (source_id - src_z*(NOC_WIDTH * NOC_HEIGHT)) % NOC_WIDTH;
				int a=0;
				if(src_x>pos_x){
					a=src_x-pos_x;
				}
				else{
					a=pos_x-src_x;
				}
				int b=0;
				if(src_y>pos_y){
					b=src_y-pos_y;
				}
				else{
					b=pos_y-src_y;
				}
				int c=0;
				if(src_z>pos_z){
					c=src_z-pos_z;
				}
				else{
					c=pos_z-src_z;
				}
				int d = a+b+c+1;
				timer[i]=temp_flit.packet_length - d;
				if (timer[i]<1){
					timer[i]=0;
				}

				tear_out[input_link_output[i]].write(reg_tear_in[i]);
				buffer_tear_out[input_link_output[i]]=1;
				//cout<<sc_time_stamp()<<" cluster "<<id<<" receive tear down pk"<<endl;

			 }



			if (reg_partial_ready_in[i] == 1) {
                if(i== TO_PROCESSOR){
					cout<<"error in cluster partial tear down"<<endl;
				}
				int k;

	            busy[i]=0;

				for(k=0;k<port_no;k++){
					  if (input_link_output[k]==i) {
					      break;
					  }
				}
				if(k == TO_PROCESSOR){
					  busy_out=0;
				}



				//cout<<sc_time_stamp()<<" router "<<id<<" receive partial to processor 0 "<<i<<endl;
				partial_out[k].write(reg_partial_in[i]);
				buffer_partial_out[k]=1;
				input_link_output[k]=-1;

			}

			if (reg_ack_ready_in[i] == 1) {

				int k;

				for(k=0;k<port_no;k++){
					  if (input_link_output[k]==i) {
					      break;
					  }
				}



				//cout<<sc_time_stamp()<<" router "<<id<<" receive ack to processor 0 "<<i<<endl;
				ack_out[k].write(reg_ack_in[i]);
				buffer_ack_out[k]=1;
			}

		}
		wait();
		//rr_pos=(rr_pos+1)%4;
		}

	}



	void arbiter() {
		int j,k;

		while(true){
			wait(0.8, SC_NS);

			k = TO_PROCESSOR;
			for (int a=0; a<port_no; a++) {
			    j=(a+rr_pos[k])%port_no;
				int direction = routing(request[j][read[j]].data_flit);
				if (read[j] != write[j] && direction == k) {
					if(j== TO_PROCESSOR) {
						cout<<"error!! the destination is the source processor"<<endl;
					}

					else {
						int direction = routing(request[j][read[j]].data_flit);

						if(direction != TO_PROCESSOR){
							cout<<"error in routing!! the direction is not the processor"<<endl;
						}

						else{
							if(busy_in==0 && busy[direction]==0){
								busy_in=1;
								busy[direction]=1;
								input_link_output[j]=direction;


								double optical_loss=0;
								if(j==TO_PROCESSOR){
									if(direction==NORTH){
										optical_loss=inject_north;
									}
									else if(direction==SOUTH){
										optical_loss=inject_south;
									}
									else if(direction==WEST){
										optical_loss=inject_west;
									}
									else if(direction==EAST){
										optical_loss=inject_east;
									}
									else if(direction==TSV_UP){
										optical_loss=inject_up;
									}
									else if(direction==TSV_DOWN){
										optical_loss=inject_down;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 1"<<endl;
									}
								}
								else if(j==NORTH){

									if(direction==SOUTH){
										optical_loss=north_south+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=north_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=north_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=north_eject+waveguide+crossing;
									}
									//else {

										//cout<<sc_time_stamp()<<" error in routing 2"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==SOUTH){

									if(direction==NORTH){
										optical_loss=south_north+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=south_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=south_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=south_eject+waveguide+crossing;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 3"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==WEST){

									if(direction==NORTH){
										optical_loss=west_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=west_south+waveguide+crossing;
									}

									else if(direction==EAST){
										optical_loss=west_east+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=west_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=west_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=west_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 4"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==EAST){

									if(direction==NORTH){
										optical_loss=east_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=east_south+waveguide+crossing;
									}

									else if(direction==WEST){
										optical_loss=east_west+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=east_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=east_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=east_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 5"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}

								else if(j==TSV_UP){


									if(direction==TO_PROCESSOR){
										optical_loss=up_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 61"<<endl;
									//}

								}
								else if(j==TSV_DOWN){


									if(direction==TO_PROCESSOR){
										optical_loss=down_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 7"<<endl;
									//}
								}

								flit_type temp_flit;
								temp_flit = request[j][read[j]].data_flit;
								ack=temp_flit.src;
								des=temp_flit.dest;

								temp_flit.loss=temp_flit.loss+optical_loss;

								router_forward_interface temp_data;
								temp_data.data_flit=temp_flit;

								//data_out[direction].write(temp_data);
								data_out[direction].write(request[j][read[j]]);
								buffer_req_out[direction]=1;
								rr_pos[k] = (j+1)%port_no;
								//rr = (k+1)%PROCESSOR_NUM;
								//reg_ack_out[j]=packet.get_code();
								read[j]=(read[j]+1)%inputbuffersize;
							}
						}

					}
				}  //end if

			}


	for (int b=PROCESSOR_NUM; b<port_no; b++) {
				k=b;
				for (int a=0; a<port_no; a++) {
					j=(a+rr_pos[k])%port_no;
					int direction = routing(request[j][read[j]].data_flit);
					if (read[j] != write[j] && direction == k) {
						if(j==TO_PROCESSOR) {

							if (busy_out==0 && busy[direction]==0){
									busy_out=1;
									busy[direction]=1;

									double optical_loss=0;
									if(j==TO_PROCESSOR){
									if(direction==NORTH){
										optical_loss=inject_north;
									}
									else if(direction==SOUTH){
										optical_loss=inject_south;
									}
									else if(direction==WEST){
										optical_loss=inject_west;
									}
									else if(direction==EAST){
										optical_loss=inject_east;
									}
									else if(direction==TSV_UP){
										optical_loss=inject_up;
									}
									else if(direction==TSV_DOWN){
										optical_loss=inject_down;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 1"<<endl;
									}
								}
								else if(j==NORTH){

									if(direction==SOUTH){
										optical_loss=north_south+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=north_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=north_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=north_eject+waveguide+crossing;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 2"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==SOUTH){

									if(direction==NORTH){
										optical_loss=south_north+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=south_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=south_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=south_eject+waveguide+crossing;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 3"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==WEST){

									if(direction==NORTH){
										optical_loss=west_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=west_south+waveguide+crossing;
									}

									else if(direction==EAST){
										optical_loss=west_east+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=west_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=west_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=west_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 4"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==EAST){

									if(direction==NORTH){
										optical_loss=east_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=east_south+waveguide+crossing;
									}

									else if(direction==WEST){
										optical_loss=east_west+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=east_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=east_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=east_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 5"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}

								else if(j==TSV_UP){


									if(direction==TO_PROCESSOR){
										optical_loss=up_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 62"<<endl;
									//}

								}
								else if(j==TSV_DOWN){


									if(direction==TO_PROCESSOR){
										optical_loss=down_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 7"<<endl;
									//}
								}

								flit_type temp_flit;
								temp_flit = request[j][read[j]].data_flit;
								temp_flit.loss=temp_flit.loss+optical_loss;

								router_forward_interface temp_data;
								temp_data.data_flit=temp_flit;


									//data_out[direction].write(temp_data);
								data_out[direction].write(request[j][read[j]]);
									buffer_req_out[direction]=1;
									rr_pos[k] = (j+1)%port_no;
									input_link_output[j]=direction;
									read[j]=(read[j]+1)%inputbuffersize;
							}

						}

						else {

							if(busy[direction]==0){
								busy[direction]=1;

								double optical_loss=0;
								if(j==TO_PROCESSOR){
									if(direction==NORTH){
										optical_loss=inject_north;
									}
									else if(direction==SOUTH){
										optical_loss=inject_south;
									}
									else if(direction==WEST){
										optical_loss=inject_west;
									}
									else if(direction==EAST){
										optical_loss=inject_east;
									}
									else if(direction==TSV_UP){
										optical_loss=inject_up;
									}
									else if(direction==TSV_DOWN){
										optical_loss=inject_down;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 1"<<endl;
									}
								}
								else if(j==NORTH){

									if(direction==SOUTH){
										optical_loss=north_south+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=north_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=north_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=north_eject+waveguide+crossing;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 2"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==SOUTH){

									if(direction==NORTH){
										optical_loss=south_north+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=south_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=south_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=south_eject+waveguide+crossing;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 3"<<endl;
									//}
									if((pos_z==0 && pos_x==0) || (pos_z==1 && pos_x==NOC_WIDTH-1)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==WEST){

									if(direction==NORTH){
										optical_loss=west_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=west_south+waveguide+crossing;
									}

									else if(direction==EAST){
										optical_loss=west_east+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=west_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=west_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=west_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 4"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}
								else if(j==EAST){

									if(direction==NORTH){
										optical_loss=east_north+waveguide+crossing;
									}
									else if(direction==SOUTH){
										optical_loss=east_south+waveguide+crossing;
									}

									else if(direction==WEST){
										optical_loss=east_west+waveguide+crossing;
									}
									else if(direction==TSV_UP){
										optical_loss=east_up+waveguide+crossing;
									}
									else if(direction==TSV_DOWN){
										optical_loss=east_down+waveguide+crossing;
									}
									else if(direction==TO_PROCESSOR){
										optical_loss=east_eject+waveguide+crossing;
									}
									else {
										cout<<sc_time_stamp()<<" error in routing 5"<<endl;
									}
									if((pos_z==0 && pos_y==NOC_HEIGHT-1) || (pos_z==1 && pos_y==0)){
										optical_loss=optical_loss-crossing;
									}
								}

								else if(j==TSV_UP){


									if(direction==TO_PROCESSOR){
										optical_loss=up_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 63"<<endl;
									//}

								}
								else if(j==TSV_DOWN){


									if(direction==TO_PROCESSOR){
										optical_loss=down_eject+waveguide;
									}
									//else {
										//cout<<sc_time_stamp()<<" error in routing 7"<<endl;
									//}
								}

								flit_type temp_flit;
								temp_flit = request[j][read[j]].data_flit;
								temp_flit.loss=temp_flit.loss+optical_loss;

								router_forward_interface temp_data;
								temp_data.data_flit=temp_flit;


								//data_out[direction].write(temp_data);
								data_out[direction].write(request[j][read[j]]);
								buffer_req_out[direction]=1;
								rr_pos[k] = (j+1)%port_no;
								//reg_data_out[direction] = packet.get_code();
								input_link_output[j]=direction;
								read[j]=(read[j]+1)%inputbuffersize;
							}
						}
				}  //end if

			}
	}
	wait();
	}
}

	void sender() {
		while(true){
				wait(0.1, SC_NS);
				for(int i=0; i<port_no; i++)	{
			          if(data_ready_out[i]==1)  {
					       data_ready_out[i]=0;
						   //data_out[i]=0;
						   //if(id==0)
								////cout<<sc_time_stamp()<<" data ready out "<<i<<" is clear"<<endl;
					  }
					  if(tear_ready_out[i]==1)  {
					       tear_ready_out[i]=0;
						   //tear_out[i]=0;
						   //if(id==0)
								////cout<<sc_time_stamp()<<" data ready out "<<i<<" is clear"<<endl;
					  }

					  if(partial_ready_out[i]==1)  {
					       partial_ready_out[i]=0;
						   //partial_out[i]=0;
						   //if(id==0)
								////cout<<sc_time_stamp()<<" data ready out "<<i<<" is clear"<<endl;
					  }

					if(ack_ready_out[i]==1)  {
					       ack_ready_out[i]=0;
						   //ack_out[i]=0;
						   //if(id==0)
								////cout<<sc_time_stamp()<<" data ready out "<<i<<" is clear"<<endl;
					  }


			    }




				wait(0.1, SC_NS);
				for (int i=0; i<port_no; i++) {
					// send packet if having data, and the receiver has empty buffer space
					if(buffer_req_out[i]==1 || buffer_tear_out[i]==1 || buffer_partial_out[i]==1 || buffer_ack_out[i]==1){
						if (buffer_req_out[i]==1) {
							data_ready_out[i].write(1);
							buffer_req_out[i]=0;
						}
						if (buffer_tear_out[i]==1) {
							tear_ready_out[i].write(1);
							buffer_tear_out[i]=0;
						}
						if (buffer_partial_out[i]==1) {
							partial_ready_out[i].write(1);
							buffer_partial_out[i]=0;
						}
						if (buffer_ack_out[i]==1) {
							ack_ready_out[i].write(1);
							buffer_ack_out[i]=0;
						}

					}

				}
				wait();

		}
	}


	void setid(int num) {
		id = num;
	}
	int  getid() {
		return id;
	}

	void setpos(int x, int y, int z) {
		pos_x = x;
		pos_y = y;
		pos_z = z;
	}
	void getpos(int &x, int &y, int &z) {
		x = pos_x;
		y = pos_y;
		z = pos_z;
	}

	void get_xyz(int address, int &x, int &y, int &z)
{
	z = address / (NOC_WIDTH * NOC_HEIGHT);
	y = (address - z*(NOC_WIDTH * NOC_HEIGHT)) / NOC_WIDTH;
	x = (address - z*(NOC_WIDTH * NOC_HEIGHT)) % NOC_WIDTH;
	assert (address == z*(NOC_WIDTH*NOC_HEIGHT)+y*NOC_WIDTH + x);
}

	int  routing(flit_type head_flit) {
		int dst=head_flit.dest;
		/*
		int index_pro;     //找出是table里面第几个
		index_pro=id*processor_no+dst;//table_number[index_pro]存放着我们要找的线路
		int d = -1;  //计数不方便，采用遍历的方法
		//cout<<dst<<" "<<src<<" "<<index_pro<<" "<<id<<" "<<getid()<<" "<<table_number[index_pro].size()<<" "<<table_direction[index_pro].size()<<" ";
		if((table_number[index_pro].size()!=0)&&(table_direction[index_pro].size()!=0)){
				for(int ii=0;ii<table_number[index_pro].size();ii++){
					if(id==table_number[index_pro][ii]){
						d=table_direction[index_pro][ii];
						//cout<<"result"<<dst<<" "<<src<<" "<<ddd<<"    ";	src不知道是啥
					}
				}
		}
		*/


		int dst_x=-1;
		int dst_y=-1;
		int dst_z=-1;
		get_xyz(dst, dst_x, dst_y, dst_z);

		int d = -1;

		if (pos_x != dst_x) {
			if (pos_x < dst_x) {
				d = RIGHT;
			}
			else if (pos_x > dst_x) {
				d = LEFT;
			}

		}
		else if (pos_y != dst_y){
			if (pos_y < dst_y) {
				d = UP;
			}
			else if (pos_y > dst_y) {
				d = DOWN;
			}

		}
		else {
			if (pos_z < dst_z) {
				d = TSV_UP;
			}
			else if (pos_z > dst_z) {
				d = TSV_DOWN;
			}
			else {
				d = TO_PROCESSOR;
			}

		}

		if (d<0) {
				assert(0);
		}

        //cout<<d<<"   ";
		return d;
	}




public:
	sc_in <bool>		clk;
	// output port, including data out, data ready and feedback signal of full buffer from receiver
	sc_out<router_forward_interface> data_out[port_no];
	sc_out<bool>					 data_ready_out[port_no];
	sc_out<router_forward_interface> ack_out[port_no];
	sc_out<bool>					 ack_ready_out[port_no];
	sc_out<router_forward_interface> tear_out[port_no];
	sc_out<bool>					 tear_ready_out[port_no];
	sc_out<router_forward_interface> partial_out[port_no];
	sc_out<bool>					 partial_ready_out[port_no];

	// input port, including data in, data ready and feedback signal of full buffer to sender
	sc_in <router_forward_interface> data_in[port_no];
	sc_in <bool>					 data_ready_in[port_no];
	sc_in <router_forward_interface> tear_in[port_no];
	sc_in <bool>					 tear_ready_in[port_no];
	sc_in <router_forward_interface> partial_in[port_no];
	sc_in <bool>					 partial_ready_in[port_no];
	sc_in <router_forward_interface> ack_in[port_no];
	sc_in <bool>					 ack_ready_in[port_no];


	bool							 busy[port_no];	// used by input port
	int								 timer[port_no];

	// used by input port
	router_forward_interface		reg_data_in[port_no];			// temp storage of input data before deciding which vc to write in
	bool							reg_data_ready_in[port_no];	// temp storage of input data ready signal
	router_forward_interface		reg_tear_in[port_no];			// temp storage of input data before deciding which vc to write in
	bool							reg_tear_ready_in[port_no];	// temp storage of input data ready signal
	router_forward_interface		reg_partial_in[port_no];			// temp storage of input data before deciding which vc to write in
	bool							reg_partial_ready_in[port_no];	// temp storage of input data ready signal
	router_forward_interface		reg_ack_in[port_no];			// temp storage of input data before deciding which vc to write in
	bool							reg_ack_ready_in[port_no];	// temp storage of input data ready signal

	bool buffer_req_out[port_no];
	bool buffer_tear_out[port_no];
	bool buffer_partial_out[port_no];
	bool buffer_ack_out[port_no];

	// used by output port
	router_forward_interface		reg_data_out[port_no];		// temp storage for output
	router_forward_interface        reg_tear_out[port_no];
	router_forward_interface        reg_partial_out[port_no];
	router_forward_interface        reg_ack_out[port_no];

	router_forward_interface		reg_head_data[port_no];
	int								buffer_counter_in[port_no];	// 0 for no space, 1 for one space
	int								buffer_counter_out[port_no];	// 0 for no space, 1 for 1 space, 2 for more than 1 space
	router_forward_interface        flag_set[port_no];
	sc_signal<int>					flag_success[port_no];

	int								input_link_output[port_no];

    router_forward_interface        request[port_no][inputbuffersize];
	int								delay[port_no];
//new
	int                 data_delay[port_no];
	int                 tear_delay[port_no];
	int                 partial_delay[port_no];
	int                 ack_delay[port_no];



	int                 read[port_no];
	int					write[port_no];

	int					packet_num;
	// internal variables
	int					id;
	int					pos_x;
	int					pos_y;
	int					pos_z;
	int					ack;
	int                 des;
	int					tear_num;
	int					partial_num;

	int					send;
	int					rr_pos[port_no];
	int					rr;
	int					rt;
	bool				ack_flag[PROCESSOR_NUM];
	bool				busy_out;
	bool				busy_in;

};

//#endif
