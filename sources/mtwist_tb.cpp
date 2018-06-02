// Mersenne Twister HLS testbench
// author Wojtek Fedorko
#include "mtwist.h"
#include <vector>
#include <cstdio> 
#include <fstream>

#include "ap_int.h"
#include "hls_stream.h"

int main(){

  int err=0;

  std::vector<unsigned long int> ref_rand_vec;

  unsigned long init=0x123;

  std::ifstream stream_rand_data_in("rand.dat");
  if (!stream_rand_data_in) {
    std::printf("ERROR: Cant open input data file\n");
    return 1;
  }


  for(int i=0;i<20624;i++){
    unsigned long int din_tmp;
    stream_rand_data_in >> std::hex>> din_tmp;
    ref_rand_vec.push_back(din_tmp);
  }

  //for(int i=0;i<1000;i++){
  //  std::printf("%8x\n",ref_rand_vec[i]);
  //}

  //seed(init);

  ap_uint<32> seed=init;
  hls::stream<ap_uint<32> > hls_output_stream;
  
  ap_uint<32> stream_length=20624;
  mtwist_core(true,seed,stream_length,hls_output_stream);
  
  //stream_length=10000;
  //mtwist_core(false,0,stream_length,hls_output_stream);

  
  unsigned int i;
  for(i=0;i<20624;i++){
    ap_uint<32> core_rand=hls_output_stream.read();
    unsigned long int ui_core_rand=core_rand;
    if(i<624){
      std::printf("%d\t%d\t%d\t--------\t%8x\n",i,i/624,i%624,ui_core_rand);
    } else if (i<3000){
      std::printf("%d\t%d\t%d\t%8x\t%8x",i,i/624,i%624,ref_rand_vec[i-624],ui_core_rand);
      if(ref_rand_vec[i-624]!=ui_core_rand) {
	std::printf("  <------------\n");
	err++;
      } else {
	std::printf("\n");
      }
    } else {
      if(ref_rand_vec[i-624]!=ui_core_rand) {
	std::printf("%d\t%d\t%d\t%8x\t%8x  <----------------\n",i,i/624,i%624,ref_rand_vec[i-624],ui_core_rand);
	err++;
      }
    }
  }


  std::printf("checked values: %d; number of errors: %d\n\n",i,err);

  if(err!=0)
    return 1;
  return 0;

}
  
  
