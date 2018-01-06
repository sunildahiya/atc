void clean_state4(){
  if (state == 4){
    serial_twoln("Chutiya:\t", stage);
    apply_correction(0);
    while (1){
      read_ultra();
      find_moving_avg();
      // read_imu();
      calc_correction(forward, left, leftRefDist);
      serial_print();
    }
  }
}
