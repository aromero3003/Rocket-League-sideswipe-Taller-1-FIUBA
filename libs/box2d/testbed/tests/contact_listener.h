#ifndef __RL_CONTACT_LISTENER__
#define __RL_CONTACT_LISTENER__

#include "box2d/b2_world_callbacks.h"

class RLContactListener : public b2ContactListener{
 public:
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

#endif  //  __RL_CONTACT_LISTENER__
