#pragma once

struct cart
{
    double Mass; 
    double XPos;
    double YPos;
    double SpeedOfCart;
    double AccelerationOfCart;
    double XForceActingOnCart;
};

struct pendulum
{
    double LengthOfPendulum;
    double AngleOfPendulum;
    double Mass;
    double XPos;
    double YPos;
    double SpeedOfPendulum;
    double AccelerationOfPendulum;
};

struct model
{
    float Gravity;
    float Friction;
    cart Cart;
    pendulum Pendulum;
};