/** Copyright (C) 2013 Robert B. Colton
***
*** This file is a part of the ENIGMA Development Environment.
***
*** ENIGMA is free software: you can redistribute it and/or modify it under the
*** terms of the GNU General Public License as published by the Free Software
*** Foundation, version 3 of the license or any later version.
***
*** This application and its source code is distributed AS-IS, WITHOUT ANY
*** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
*** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
*** details.
***
*** You should have received a copy of the GNU General Public License along
*** with this code. If not, see <http://www.gnu.org/licenses/>
**/
#include "Universal_System/collisions_object.h"
#include "Universal_System/instance_system.h" //iter
//#include "Universal_System/roomsystem.h"
#include "Collision_Systems/collision_mandatory.h" //iter
#include "Universal_System/instance.h"

#include <string>
#include <stdio.h>
#include <vector>
using std::vector;
//using namespace std;

#include <Box2D/Box2D.h>
#include "functions.h"
bool systemPaused = false;

struct worldInstance { 
  b2World* world;
  // Prepare for simulation. Typically we use a time step of 1/60 of a
  // second (60Hz) and 10 iterations. This provides a high quality simulation
  // in most game scenarios.
  float32 timeStep = 1.0f / 30.0f;
  int32 velocityIterations = 8;
  int32 positionIterations = 3;
  worldInstance() 
  {
    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    world = new b2World(gravity);
  }
  void world_update();
}; 
void worldInstance::world_update() 
{
  if (!systemPaused) {
    world->Step(timeStep, velocityIterations, positionIterations);
  }
}
vector<worldInstance> worlds(0);

struct fixtureInstance { 
  int world;
  b2Body* body;
  b2Fixture* fixture;
  b2Shape* shape;
  fixtureInstance() 
  {
  }
}; 
vector<fixtureInstance> fixtures(0);

/* This is just place holder shit to get the fuckin linker shut the fuckin hell up */
enigma::instance_t collision_rectangle(double x1, double y1, double x2, double y2, int obj, bool prec, bool notme)
{

}

namespace enigma
{ 
  void *get_collision_mask(sprite* spr, unsigned char* input_data, collision_type ct) // It is called for every subimage of every sprite loaded.
  {
    return 0;
  }

  void free_collision_mask(void* mask)
  {
  }
};

bool place_free(double x,double y)
{
  return true;
}

bool place_meeting(double x, double y, int object)
{
  return false;
}

/* This is where the actual physics_* functions start at */

int physics_world_create() 
{
  int i = worlds.size();
  worlds.resize(i + 1);
  worlds[i] = worldInstance();
  return i;
}

void physics_world_update(int index) 
{
  if (unsigned(index) >= worlds.size() || index < 0)
  {
    return;
  }
  else
  {
    worlds[index].world_update();
  }
}

void physics_fixture_create()
{

}

int physics_fixture_create(int world) 
{
  if (unsigned(world) >= worlds.size() || world < 0)
  {
    return -1;
  }
  else
  {
    int i = fixtures.size();
    fixtures.resize(i + 1);
    fixtureInstance fixture = fixtureInstance();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    fixture.body = worlds[world].world->CreateBody(&bodyDef);
    fixtures[i] = fixture;
    return i;
  }
}

void physics_fixture_bind()
{
  // binds a fixture to an object, im not writing this fuck YYG
}

void physics_fixture_set_collision_group(int id, int group)
{
  //fixtures[id].fixture->filter.groupIndex = group;
}

void physics_fixture_delete(int id)
{

}

void physics_fixture_set_box_shape(int id, double halfwidth, double halfheight)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    b2PolygonShape shape;
    shape.SetAsBox(halfwidth, halfheight);
    fixtures[id].shape = &shape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtures[id].fixture = fixtures[id].body->CreateFixture(&fixtureDef);
  }
}

void physics_fixture_set_circle_shape(int id, double radius) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    b2CircleShape shape;
    shape.m_radius = radius;
    fixtures[id].shape = &shape;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtures[id].fixture = fixtures[id].body->CreateFixture(&fixtureDef);
  }
}

void physics_fixture_set_transform(int id, double x, double y, double angle)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetTransform(b2Vec2(x, y), angle);
  }
}

void physics_fixture_set_position(int id, double x, double y)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetTransform(b2Vec2(x, y), fixtures[id].body->GetAngle());
  }
}

void physics_fixture_set_angle(int id, double angle)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetTransform(fixtures[id].body->GetPosition(), angle);
  }
}

void physics_fixture_set_density(int id, double density) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    // technically studio makes it so 0 density, means infinite density and just makes it
    // a static object, but im just gonna go ahead and comment that out cause its fuckin stupid
    //if (density == 0) {
      //fixtures[id].body->SetType(b2_staticBody);
    //} else {
      fixtures[id].fixture->SetDensity(density);
      fixtures[id].body->ResetMassData();
    //}
  }
}

void physics_fixture_set_friction(int id, double friction) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    fixtures[id].fixture->SetFriction(friction);
    fixtures[id].body->ResetMassData();
  }
}

void physics_fixture_set_linear_damping(int id, double damping)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    fixtures[id].body->SetLinearDamping(damping);
  }
}

void physics_fixture_set_angular_damping(int id, double damping)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    fixtures[id].body->SetAngularDamping(damping);
  }
}

void physics_fixture_set_restitution(int id, double restitution)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    fixtures[id].fixture->SetRestitution(restitution);
  }
}

void physics_fixture_set_sensor(int id, bool state)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else 
  {
    fixtures[id].fixture->SetSensor(state);
  }
}

void physics_fixture_set_awake(int id, bool state)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetAwake(state);
  }
}

void physics_fixture_set_static(int id)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetType(b2_staticBody);
  }
}

void physics_fixture_set_kinematic(int id)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetType(b2_kinematicBody);
  }
}

void physics_fixture_set_dynamic(int id)
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return;
  }
  else
  {
    fixtures[id].body->SetType(b2_dynamicBody);
  }
}

double physics_fixture_get_angle(int id) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return 0;
  }
  else
  {
    return fixtures[id].body->GetAngle();
  }
}

double physics_fixture_get_x(int id) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return 0;
  }
  else
  {
    return fixtures[id].body->GetPosition().x;
  } 
}

double physics_fixture_get_y(int id) 
{
  if (unsigned(id) >= fixtures.size() || id < 0)
  {
    return 0;
  }
  else
  {
    return fixtures[id].body->GetPosition().y;
  }
}

void physics_pause_enable(bool pause)
{
  systemPaused = pause;
}

void physics_mass_properties(double mass, double local_center_x, double local_center_y, double inertia)
{
  // same as physics_fixture_set_mass except it doesnt need an id, uses the currently bound fixture
  // of whatever is calling the function, im not writing it cause its stupid
}

void physics_draw_debug()
{
  // draws the currently bound fixture's shape with draw color, fuck that let the end programmer have control
}
