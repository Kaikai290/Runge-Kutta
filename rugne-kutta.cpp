#pragma Once

#include "model.h"
/*
This is the State-Space Representation of my system of equations

y = [theta, theta dot, X(t), X(t) dot]
y dot = [theta dot , theta dot dot, X(t) dot, X(t) dot dot]
y dot = [theta dot, (theta * m)/M + u(t)/M, X(t) dot, theta(M+m)/M + u(t)/M]

We m be the weight of pendulum, M be the weight of the Cart and u(t) by the force applied to the cart.
*/

struct SystemStates
{
    double ThetaDot;
    double ThetaDotDot;
    double Xdot;
    double Xdotdot;
};

void RK4(model *Model)
{
    double h;
    h = 0.02;
    double U;
    U = 0;
    SystemStates k1;
    k1.ThetaDot = Model->Pendulum.SpeedOfPendulum;
    k1.ThetaDotDot = ((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k1.Xdot = Model->Cart.SpeedOfCart;
    k1.Xdotdot = ((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k2;
    k2.ThetaDot = Model->Pendulum.SpeedOfPendulum + (h * k1.ThetaDot)/2;
    k2.ThetaDotDot = ((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k2.Xdot = Model->Cart.SpeedOfCart + (h * k1.Xdot)/2;
    k2.Xdotdot = ((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k3;
    k3.ThetaDot = Model->Pendulum.SpeedOfPendulum + (h * k2.ThetaDot)/2;
    k3.ThetaDotDot = ((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k3.Xdot = Model->Cart.SpeedOfCart + (h * k2.Xdot)/2;
    k3.Xdotdot = ((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    SystemStates k4;
    k4.ThetaDot = Model->Pendulum.SpeedOfPendulum + (h * k3.ThetaDot);
    k4.ThetaDotDot = ((Model->Pendulum.AngleOfPendulum * Model->Pendulum.Mass) / Model->Cart.Mass) + (U / Model->Cart.Mass);
    k4.Xdot = Model->Cart.SpeedOfCart + (h * k1.Xdot);
    k4.Xdotdot = ((Model->Pendulum.AngleOfPendulum * (Model->Cart.Mass + Model->Pendulum.Mass)) / Model->Cart.Mass) + (U / Model->Cart.Mass);

    Model->Pendulum.AngleOfPendulum = Model->Pendulum.AngleOfPendulum + (h/6)*(k1.ThetaDot + 2 * k2.ThetaDot + 2*k3.ThetaDot + k4.ThetaDot);
    Model->Pendulum.SpeedOfPendulum = Model->Pendulum.SpeedOfPendulum + (h/6)*(k1.ThetaDotDot + 2 * k2.ThetaDotDot + 2*k3.ThetaDotDot + k4.ThetaDotDot);
    Model->Cart.XPos = Model->Pendulum.XPos + (h/6)*(k1.Xdot + 2 * k2.Xdot + 2*k3.Xdot + k4.Xdot);
    Model->Cart.SpeedOfCart = Model->Pendulum.SpeedOfPendulum + (h/6)*(k1.Xdotdot + 2 * k2.Xdotdot + 2*k3.Xdotdot + k4.Xdotdot);


}
