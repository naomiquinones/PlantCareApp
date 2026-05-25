#ifndef CAREEVENT_H
#define CAREEVENT_H

#include <string>

/**
 * CareEvent represents a single care action performed on a plant.
 * Maps to the care_events table in the database.
 * Event types include: water, fertilize, repot, prune, root_prune.
 */
class CareEvent {
private:
    int id;
    int plantId;
    std::string eventType;
    std::string eventDate;
    std::string notes;

public:
    CareEvent();
    CareEvent(int plantId, const std::string& eventType, const std::string& eventDate);

    int getId() const;
    int getPlantId() const;
    std::string getEventType() const;
    std::string getEventDate() const;
    std::string getNotes() const;

    void setId(int id);
    void setPlantId(int plantId);
    void setEventType(const std::string& eventType);
    void setEventDate(const std::string& eventDate);
    void setNotes(const std::string& notes);

    void display() const;
};

#endif