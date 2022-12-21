#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "rocket.h"

class Controller {
 public:
  Controller();
  void HandleInput(bool &running, bool& endlessRepeat, Rocket &rocket) const;
  void CheckRestart(bool& restart, bool& quit) const;

 private:
  void ChangeBoost(Rocket &rocket, Rocket::Direction input) const;
  void ChangeRotation(Rocket& rocket, Rocket::Rotation input) const;
  bool KEYS[322];

};

#endif