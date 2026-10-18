#include "gestor_alertas.hpp"

namespace pulso::alertas {

void GestorAlertas::addAlerta(const AlertaUmbral& alerta) {
    alertas_.push_back(alerta);
}

void GestorAlertas::setCallback(std::function<void(const std::string&)> callback) {
    callback_ = callback;
}

void GestorAlertas::evaluar(const pulso::MetricSnapshot& snap) const {
    // Si no hay callback registrado, no hacemos nada
    if (!callback_) {
        return;
    }

    // Si no hay alertas registradas, no hacemos nada
    if (alertas_.empty()) {
        return;
    }

    // Evaluar cada alerta y llamar callback solo para las que se disparan
    for (const auto& alerta : alertas_) {
        if (alerta.evaluar(snap)) {
            callback_(alerta.mensaje());
        }
    }
}

std::size_t GestorAlertas::cantidadAlertas() const {
    return alertas_.size();
}

const std::vector<AlertaUmbral>& GestorAlertas::getAlertas() const {
    return alertas_;
}
} // namespace pulso::alertas
