// 10/02/2023 -- Nikilesh
#include "Subsystem.h"
#include "LinearKalmanFilter.h"
#include "system_messages/StateEstimatorMsg.h"
#ifdef BUILD_ENV_rocket
#include <Arduino.h>
#endif

class StateEstimator : public Subsystem
{
    public:
        explicit StateEstimator(uint8_t id, float tstep) : Subsystem(id) {
            Filter = new LinearKalmanFilter(tstep, 20, 1);
        };
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        float altitudeEstimate(BarometerDataMsg *msg);
        void on_message(SystemMessage *msg) override;



       // SUBSYSTEM_NO_MESSAGE_HANDLER;
        SUBSYSTEM_NAME("StateEstimator");
    
    private:
        float altitude = 0;
        float velocity = 0;

        bool start = 0;
        bool recievedBaro = 0;
        bool recievedAcc = 0;
        
        float yAcceleration = 0;
        float pressure = 0;

        float currentMillis = 0;
        float prevMillis = 0;
        LinearKalmanFilter * Filter;
        AccelerometerDataMsg *acceleration;
        BarometerDataMsg *altimeter;
      
};

