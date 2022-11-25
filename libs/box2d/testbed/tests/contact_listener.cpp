#include "contact_listener.h"
#include "box2d/b2_world_callbacks.h"
#include <box2d/box2d.h>

void RLContactListener::BeginContact(b2Contact *contact){
    b2ContactListener::BeginContact(contact);
}

void RLContactListener::EndContact(b2Contact *contact){
    b2ContactListener::EndContact(contact);
}
