/*Description: This code uses three types of detectors to detect 
different types of leptons (electrons/muons). It also displays information
about the properties of those leptons (from appropriate input) and how many
relevant particles were detected.
Author: Hassan Hashmi
Date: 07/03/2024*/ 

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> 
#include <vector>

const double speed_of_light = 2.99792458e8; 

class lepton 
{
private:
  std::string particle_type;
  double rest_mass;          
  int charge;                
  double velocity;           
  double beta;   
public:
  lepton() = default;
  lepton(const std::string input_particle_type, double input_mass, int input_charge, double input_velocity):
    particle_type{input_particle_type}, rest_mass{input_mass}, charge{input_charge}, velocity{input_velocity}
    {
      if(velocity >= speed_of_light) 
        std::cout<<"\nOne or more of your beta values are incorrect, please ensure v < c for all particles."<<std::endl;
      beta = velocity / speed_of_light;  
    }
  ~lepton(){} 
  void set_particle_type(const std::string &input_particle_type) {particle_type = input_particle_type;}
  void set_rest_mass(double input_mass) {rest_mass = input_mass;}
  void set_charge(int input_charge) 
  {
    if(input_charge == 1 || input_charge == -1)
      charge = input_charge;
    else
      std::cout<<"Invalid charge. Must be 1 (for particles) or -1 (for anti-particles)"<<std::endl; 
  }
  void set_velocity(double input_velocity) 
  {
    if(input_velocity < speed_of_light) 
    {
      velocity = input_velocity;
      beta = velocity / speed_of_light;
    } 
    else 
      std::cout<<"Invalid velocity. Please ensure v < c. "<<std::endl;
  }
  std::string get_particle_type() const {return particle_type;}
  double get_rest_mass() const {return rest_mass;}
  int get_charge() const {return charge;}
  double get_velocity() const {return velocity;}
  double get_beta() const {return beta;}
  friend void print_lepton_data(const lepton &input_lepton);  //declare friend function to access data members outside class
};

class lepton_detector 
{
private:
  std::string detector_type;           
  bool detector_status;         
  int number_of_particles;
public:
  lepton_detector() = default;
  lepton_detector(const std::string &input_detector_type, const bool &input_detector_status) : detector_type{input_detector_type}, 
  detector_status{input_detector_status}, number_of_particles{0} {}    
  ~lepton_detector(){}
  void turn_off_detector() 
  {
    detector_status = false;
    std::cout<<"\nThe "<<detector_type<<" is off."<<std::endl;
  }
  void turn_on_detector() 
  {
    detector_status = true;
    std::cout <<"The "<<detector_type<<" is on."<<"\n"<<std::endl;
  }
  void print_detector_data() const {std::cout<<"\nThe "<<detector_type<<" detected "<<number_of_particles<<" particles\n";}
  int detect_particle(const lepton &particle) 
  {
    if (detector_status == true && 
    ((detector_type == "tracker" && 
      (particle.get_particle_type() == "electron" || 
       particle.get_particle_type() == "muon" || 
       particle.get_particle_type() == "anti-electron" || 
       particle.get_particle_type() == "anti-muon")) || 
     (detector_type == "calorimeter" && 
      (particle.get_particle_type() == "electron" || 
       particle.get_particle_type() == "anti-electron")) ||
     (detector_type == "muon chamber" && 
      (particle.get_particle_type() == "muon" || 
       particle.get_particle_type() == "anti-muon"))))
    {
      number_of_particles++;
      std::cout<<"The "<<detector_type<<" detected a "<<particle.get_particle_type()<< std::endl; 
      return 1;
    }
    else if (detector_status == false || 
      particle.get_particle_type() != "electron" || 
      particle.get_particle_type() != "muon" ||
      particle.get_particle_type() != "anti-electron" || 
      particle.get_particle_type() != "anti-muon")
        return 0;
    else
      return 0;
  };
};

void print_lepton_data(const lepton &input_lepton) 
{
  std::cout<<std::fixed<<std::setprecision(3);
  std::cout<<"\nType of lepton: "<<input_lepton.particle_type<<std::endl;
  std::cout<<"Rest Mass (MeV): "<<input_lepton.rest_mass<<std::endl;
  std::cout<<"Charge: "<<input_lepton.charge<<std::endl;
  std::cout<<"Velocity (m/s): "<<input_lepton.velocity<<std::endl;
  std::cout<<"Beta Value: "<<input_lepton.beta<<"\n"<<std::endl;
}

int main() 
{
  std::vector<lepton> lepton_information_vector = 
    {
      lepton("electron", 0.511, -1, 1.2e9), 
      lepton("electron", 0.511, -1, 4.6e7),
      lepton("muon", 105.7, -1, 3.3e6),
      lepton("muon", 105.7, -1, 7.1e7),
      lepton("muon", 105.7, -1, 6.3e7),
      lepton("muon", 105.7, -1, 9.1e5), 
      lepton("anti-electron", 0.511, 1, 9.0e7),
      lepton("anti-muon", 105.7, 1, 7.0e7)      
    };
  lepton_detector tracker("tracker", false);
  lepton_detector calorimeter("calorimeter", false);
  lepton_detector muon_chamber("muon chamber", false);
  tracker.turn_on_detector();
  calorimeter.turn_on_detector();
  muon_chamber.turn_on_detector();
  for(const lepton &particle : lepton_information_vector) 
  {
    tracker.detect_particle(particle);
    calorimeter.detect_particle(particle);
    muon_chamber.detect_particle(particle);
  }
  tracker.print_detector_data();
  calorimeter.print_detector_data();
  muon_chamber.print_detector_data();
  for(const lepton &particle : lepton_information_vector) 
  {
    print_lepton_data(particle);
  }
  tracker.turn_off_detector();
  calorimeter.turn_off_detector();
  muon_chamber.turn_off_detector();
  return 0;
}