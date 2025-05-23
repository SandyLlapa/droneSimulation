#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "DroneObserver.h"
#include "PackageObserver.h"
#include "RechargeStationObserver.h"
#include "RobotObserver.h"
#include "CompositeFactory.h"
#include "Drone.h"
#include "RechargeStation.h"
#include "IController.h"
#include "IEntity.h"
#include "Robot.h"
#include "graph.h"
#include <deque>
#include <map>
#include <set>

class RechargeStation;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   * 
   * @param id of the entity to be removed
  */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns IGraph* graph pointer
  */
  const routing::IGraph* getGraph();

  /**
   * @brief Adds a recharge station to the vector of recharge
   * stations (rechargeStations).
   * @param station The recharge station to add to the vector.
   **/
  void addRechargeStation(RechargeStation* station);

  /**
   * @brief Returns the vector of recharge stations (rechargeStations).
   * @return The vector of recharge stations.
   **/
  std::vector<RechargeStation*> getRechargeStations();

  /**
   * @brief Sends a notification to the web view.
   * @param notification The notification to send.
   **/
  void addNotification(const std::string& notification);

  std::deque<Package*> scheduledDeliveries;

 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  void removeFromSim(int id);
  const routing::IGraph* graph;
  CompositeFactory entityFactory;
  std::vector<RechargeStation*> rechargeStations;

  DroneObserver* droneObserver = new DroneObserver();
  PackageObserver* packageObserver = new PackageObserver();
  RobotObserver* robotObserver = new RobotObserver();
  RechargeStationObserver* rechargeStationObserver
                                      = new RechargeStationObserver();
};

#endif
