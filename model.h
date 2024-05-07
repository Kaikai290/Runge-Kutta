struct cart
{
    double Mass; 
    double XPos;
    double YPos;
    double XSpeedOfCart;
    double YSpeedOfCart;
    double XAccelerationOfCart;
    double YAccelerationOfCart;
    double XForceActingOnCart;
};

struct pendulum
{
    double LengthOfPendulum;
    double AngleOfPendulum;
    double Mass;
    double XPos;
    double YPos;
    double XSpeedOfPendulum;
    double YSpeedOfPendulum;
    double XAccelerationOfPendulum;
    double YAccelerationOfPendulum;
};

struct model
{
    float Gravity;
    float Friction;
    cart Cart;
    pendulum Pendulum;
};