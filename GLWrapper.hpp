#ifndef __GLWRAPPER_H__
#define __GLWRAPPER_H__

class GL{
public:
    static GL* get();

private:
    GL();
    ~GL();
};

#endif // __GLWRAPPER_H__