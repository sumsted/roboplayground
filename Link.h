#ifndef LINK_H
#define LINK_H

class Link {
  public:
    Link(int pwire, void(*ptake_action)(*char));
    void setup();
  private:
    void receive_data(int num_bytes);
    void send_data(char *data);
    int wire;
    void(*take_action)(int, int);
};

#endif
