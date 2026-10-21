#include "http/handler_prometheus.hpp"
#include "formatters/formatter_prometheus.hpp"

#include <httplib.h>

namespace pulso::http {

void registrarPrometheus(
    httplib::Server& servidor,
    const pulso::storage::Storage& storage)
{
    servidor.Get("/metrics/prometheus",
        [&storage](const httplib::Request& /*req*/, httplib::Response& res)
        {
            auto snapshot = storage.ultimo();

            if (!snapshot) {
                // Prometheus tolera respuestas vacías; devolvemos 200 con body vacío.
                res.status = 200;
                res.set_content("", "text/plain; version=0.0.4");
                return;
            }

            pulso::formatters::FormatterPrometheus formatter;
            std::string body = formatter.formatear(*snapshot);

            res.status = 200;
            res.set_content(body, "text/plain; version=0.0.4");
        });
}

} // namespace pulso::http
