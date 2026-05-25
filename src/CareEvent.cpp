#include "CareEvent.h"
#include <iostream>
using namespace std;

CareEvent::CareEvent() : id(0), plantId(0), eventType(""), eventDate(""), notes("") {}
CareEvent::CareEvent(int plantId, const string& eventType, const string& eventDate)
    : id(0), plantId(plantId), eventType(eventType), eventDate(eventDate), notes("") {}
int CareEvent::getId() const { return id; }
int CareEvent::getPlantId() const { return plantId; }
string CareEvent::getEventType() const { return eventType; }
string CareEvent::getEventDate() const { return eventDate; }
string CareEvent::getNotes() const { return notes; }
void CareEvent::setId(int id) { this->id = id; }
void CareEvent::setPlantId(int plantId) { this->plantId = plantId; }
void CareEvent::setEventType(const string& eventType) { this->eventType = eventType; }
void CareEvent::setEventDate(const string& eventDate) { this->eventDate = eventDate; }
void CareEvent::setNotes(const string& notes) { this->notes = notes; }
void CareEvent::display() const { cout << "[CareEvent::display] not yet implemented\n"; }
