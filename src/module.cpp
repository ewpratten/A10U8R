#include "plugin.hpp"


struct A10u8r_module : Module {
	enum ParamId {
		VALUE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INPUT_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTPUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	A10u8r_module() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(VALUE_PARAM, 0.f, 1.f, 1.f, "Multiplier");
		configInput(INPUT_INPUT, "Signal");
		configOutput(OUTPUT_OUTPUT, "Signal");
	}

	void process(const ProcessArgs& args) override {

		float value = params[VALUE_PARAM].getValue();
		float input = inputs[INPUT_INPUT].getVoltage();
		outputs[OUTPUT_OUTPUT].setVoltage(value * input);
	}
};


struct A10u8r_moduleWidget : ModuleWidget {
	A10u8r_moduleWidget(A10u8r_module* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/a10u8r_module.svg")));

		// Set the screw positions
		addChild(createWidget<ScrewSilver>(Vec(0, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(0, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// Configure I/O
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(5.08, 64.25)), module, A10u8r_module::VALUE_PARAM));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 31.102)), module, A10u8r_module::INPUT_INPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(5.08, 110.491)), module, A10u8r_module::OUTPUT_OUTPUT));
	}
};


Model* modelA10u8r_module = createModel<A10u8r_module, A10u8r_moduleWidget>("a10u8r_module");