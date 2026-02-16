#pragma once

class initialize_auto {
    private:
    double globalX, globalY, globalHeading;
    public:
    initialize_auto(double GlobalX, double GlobalY, double GlobalHeading);
    double selectedX();
    double selectedY();
    double selectedHeading();
};

extern initialize_auto skills_;
extern initialize_auto right_;
extern initialize_auto left_;