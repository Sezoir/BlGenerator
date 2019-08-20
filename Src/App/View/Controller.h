#pragma once

namespace App::View {
        class Controller
        {
        public:
            Controller() {}
            virtual ~Controller() {}

            Controller(const Controller&) = delete;

            virtual void makeConnections()
            {

            }
        };

    }

