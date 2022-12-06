#include <box2d/box2d.h>
#include "GameObjects/Constants.h"

class RLContactListener : public b2ContactListener {
 public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
};


