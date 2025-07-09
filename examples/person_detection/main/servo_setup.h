extern "C"
{
    void servo_init();
    void servo_moveto(int panto,int tiltto);
    void servo_panto(int moveto);
    void servo_tiltto(int moveto);
}