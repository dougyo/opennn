//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   U N S C A L I N G   L A Y E R    C L A S S
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#include "unscaling_layer.h"

namespace OpenNN
{

/// Default constructor.

UnscalingLayer::UnscalingLayer() : Layer()
{
    set();
}


/// Outputs number constructor.

UnscalingLayer::UnscalingLayer(const Index& new_neurons_number) : Layer()
{
    set(new_neurons_number);
}


/// Outputs descriptives constructor.

UnscalingLayer::UnscalingLayer(const Tensor<Descriptives, 1>& new_descriptives) : Layer()
{
    set(new_descriptives);
}


/// XML constructor.

UnscalingLayer::UnscalingLayer(const tinyxml2::XMLDocument& unscaling_layer_document) : Layer()
{
    set(unscaling_layer_document);
}


/// Copy constructor.

UnscalingLayer::UnscalingLayer(const UnscalingLayer& other_unscaling_layer) : Layer()
{
    set(other_unscaling_layer);
}


/// Destructor.

UnscalingLayer::~UnscalingLayer()
{
}


Tensor<Index, 1> UnscalingLayer::get_input_variables_dimensions() const
{
    Tensor<Index, 1> input_variables_dimensions(1);

    input_variables_dimensions.setConstant(descriptives.size());

    return input_variables_dimensions;
}


Index UnscalingLayer::get_inputs_number() const
{
    return descriptives.size();
}


/// Returns the number of unscaling neurons in this layer.

Index UnscalingLayer::get_neurons_number() const
{
    return descriptives.size();
}


/// Returns all the available descriptives of the inputs and output variables.
/// The format is a vector of pointers to vectors of size ten:
/// <ul>
/// <li> Mean of variables.
/// <li> Standard deviation of variables.
/// <li> Minimum of variables.
/// <li> Maximum of variables.
/// </ul>

Tensor<Descriptives, 1> UnscalingLayer::get_descriptives() const
{
    return descriptives;
}


/// Returns a single matrix with the descriptives of all unscaling neurons.
/// The number of rows is the number of unscaling neurons,
/// and the number of columns is 4(minimum, maximum, mean and standard deviation).

Tensor<type, 2> UnscalingLayer::get_descriptives_matrix() const
{
    const Index neurons_number = get_neurons_number();

    Tensor<type, 2> descriptives_matrix(neurons_number, 4);

    for(Index i = 0; i < neurons_number; i++)
    {

        descriptives_matrix(i,0) = descriptives(i).minimum;
        descriptives_matrix(i,1) = descriptives(i).maximum;
        descriptives_matrix(i,2) = descriptives(i).mean;
        descriptives_matrix(i,3) = descriptives(i).standard_deviation;
    }

    return descriptives_matrix;
}


/// Returns a vector with the minimum values of all unscaling neurons.
/// The size is the number of neurons in the layer.

Tensor<type, 1> UnscalingLayer::get_minimums() const
{
    const Index neurons_number = get_neurons_number();

    Tensor<type, 1> minimums(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        minimums[i] = descriptives[i].minimum;
    }

    return minimums;
}


/// Returns a vector with the maximum values of all unscaling neurons.
/// The size is the number of neurons in the layer.

Tensor<type, 1> UnscalingLayer::get_maximums() const
{
    const Index neurons_number = get_neurons_number();

    Tensor<type, 1> maximums(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        maximums[i] = descriptives[i].maximum;
    }

    return maximums;
}


/// Returns the method used for unscaling
///(no unscaling, minimum and maximum or mean and standard deviation).

const UnscalingLayer::UnscalingMethod& UnscalingLayer::get_unscaling_method() const
{
    return unscaling_method;
}


/// Returns a string with the name of the method used for unscaling
///("MinimumMaximum", "MeanStandardDeviation", "Logarithmic" or "NoUnscaling").

string UnscalingLayer::write_unscaling_method() const
{
    if(unscaling_method == NoUnscaling)
    {
        return "NoUnscaling";
    }
    else if(unscaling_method == MinimumMaximum)
    {
        return "MinimumMaximum";
    }
    else if(unscaling_method == MeanStandardDeviation)
    {
        return "MeanStandardDeviation";
    }
    else if(unscaling_method == Logarithmic)
    {
        return "Logarithmic";
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "string write_unscaling_method() const method.\n"
               << "Unknown unscaling method.\n";

        throw logic_error(buffer.str());
    }
}


/// Returns a string with the name of the method used for unscaling,
/// as paragraph text.

string UnscalingLayer::write_unscaling_method_text() const
{
    if(unscaling_method == NoUnscaling)
    {
        return "no unscaling";
    }
    else if(unscaling_method == MeanStandardDeviation)
    {
        return "mean and standard deviation";
    }
    else if(unscaling_method == MinimumMaximum)
    {
        return "minimum and maximum";
    }
    else if(unscaling_method == Logarithmic)
    {
        return "logarithmic";
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "string write_unscaling_method_text() const method.\n"
               << "Unknown unscaling method.\n";

        throw logic_error(buffer.str());
    }
}


/// Returns true if messages from this class are to be displayed on the screen, or false if messages
/// from this class are not to be displayed on the screen.

const bool& UnscalingLayer::get_display() const
{
    return display;
}


/// Sets the unscaling layer to be empty.

void UnscalingLayer::set()
{
    descriptives.resize(0);

    set_default();
}


void UnscalingLayer::set_inputs_number(const Index& new_inputs_number)
{
    descriptives.resize(new_inputs_number);
}


void UnscalingLayer::set_neurons_number(const Index& new_neurons_number)
{
    descriptives.resize(new_neurons_number);
}


/// Sets a new size in the unscaling layer.
/// It also sets the members to their default values.

void UnscalingLayer::set(const Index& new_neurons_number)
{
    descriptives.resize(new_neurons_number);

    set_default();
}


/// Sets the size of the unscaling layer and the descriptives values.
/// @param new_descriptives Vector of vectors containing the minimums, maximums, means and standard deviations for the unscaling layer.
/// The size of this vector must be 4.
/// The size of each subvector will be the size of the unscaling layer.

void UnscalingLayer::set(const Tensor<Descriptives, 1>& new_descriptives)
{
    descriptives = new_descriptives;

    set_default();
}


/// Sets the unscaling layer members from a XML document.
/// @param new_unscaling_layer_document Pointer to a TinyXML document containing the member data.

void UnscalingLayer::set(const tinyxml2::XMLDocument& new_unscaling_layer_document)
{
    set_default();

    from_XML(new_unscaling_layer_document);
}


/// Sets the members of this object to be the members of another object of the same class.

void UnscalingLayer::set(const UnscalingLayer& new_unscaling_layer)
{
    descriptives = new_unscaling_layer.descriptives;

    unscaling_method = new_unscaling_layer.unscaling_method;

    display = new_unscaling_layer.display;
}


/// This member sets the default values for the unscaling layer:
/// <ul>
/// <li> Minimus: -1 for all unscaling neurons.
/// <li> Maximums: 1 for al unscaling neurons.
/// <li> Means: 0 for all unscaling neurons.
/// <li> Standard deviations 1 for all unscaling neurons.
/// <li> Unscaling method: Minimum and maximum.
/// <li> Display: True.
/// </ul>

void UnscalingLayer::set_default()
{
    layer_name = "unscaling_layer";

    set_unscaling_method(MinimumMaximum);

    set_display(true);

    layer_type = Unscaling;
}


/// Sets the descriptives for all the neurons in the unscaling layer from a vector.
/// The size of this vector must be equal to the number of unscaling neurons.
/// @param new_descriptives Unscaling neurons descriptives.

void UnscalingLayer::set_descriptives(const Tensor<Descriptives, 1>& new_descriptives)
{
#ifdef __OPENNN_DEBUG__

    const Index neurons_number = get_neurons_number();

    const Index new_descriptives_size = new_descriptives.size();

    if(new_descriptives_size != neurons_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "void set_descriptives(const Tensor<Descriptives, 1>&) method.\n"
               << "Size of descriptives (" << new_descriptives_size << ") must be equal to number of unscaling neurons (" << neurons_number << ").\n";

        throw logic_error(buffer.str());
    }

#endif

    // Set all descriptives

    descriptives = new_descriptives;
}


void UnscalingLayer::set_descriptives_eigen(const Tensor<type, 2>& new_descriptives)
{
    const Index neurons_number = get_neurons_number();

    Tensor<Descriptives, 1> descriptives(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        descriptives[i].set_minimum(new_descriptives(static_cast<long long>(i), 0));
        descriptives[i].set_maximum(new_descriptives(static_cast<long long>(i), 1));
        descriptives[i].set_mean(new_descriptives(static_cast<long long>(i), 2));
        descriptives[i].set_standard_deviation(new_descriptives(static_cast<long long>(i), 3));
    }

    set_descriptives(descriptives);
}


/// Sets the minimum, maximum, mean and standard deviation values of a single unscaling neuron.
/// @param i Index of unscaling neuron.
/// @param item_descriptives  Descriptives values for that neuron.

void UnscalingLayer::set_item_descriptives(const Index& i, const Descriptives& item_descriptives)
{
    descriptives[i] = item_descriptives;
}


/// Sets the minimum value of a given unscaling neuron.
/// @param i Index of unscaling neuron.
/// @param new_minimum Minimum value.

void UnscalingLayer::set_minimum(const Index& i, const type& new_minimum)
{
    descriptives[i].set_minimum(new_minimum);
}


/// Sets the maximum value of a given unscaling neuron.
/// @param i Index of unscaling neuron.
/// @param new_maximum Maximum value.

void UnscalingLayer::set_maximum(const Index& i, const type& new_maximum)
{
    descriptives[i].set_maximum(new_maximum);
}


/// Sets the mean value of a given unscaling neuron.
/// @param i Index of unscaling neuron.
/// @param new_mean Mean value.

void UnscalingLayer::set_mean(const Index& i, const type& new_mean)
{
    descriptives[i].set_mean(new_mean);
}


/// Sets the standard deviation value of a given unscaling neuron.
/// @param i Index of unscaling neuron.
/// @param new_standard_deviation Standard deviation value.

void UnscalingLayer::set_standard_deviation(const Index& i, const type& new_standard_deviation)
{
    descriptives[i].set_standard_deviation(new_standard_deviation);
}


/// Sets the method to be used for unscaling the outputs from the neural network
/// @param new_unscaling_method New unscaling method for the output variables.

void UnscalingLayer::set_unscaling_method(const UnscalingLayer::UnscalingMethod& new_unscaling_method)
{
    unscaling_method = new_unscaling_method;
}


/// Sets the method to be used for unscaling the outputs from the neural network
/// The argument is a string containing the name of the method("NoUnscaling", "MeanStandardDeviation", "MinimumMaximum" or "Logarithmic").
/// @param new_unscaling_method New unscaling method for the output variables.

void UnscalingLayer::set_unscaling_method(const string& new_unscaling_method)
{
    if(new_unscaling_method == "NoUnscaling")
    {
        set_unscaling_method(NoUnscaling);
    }
    else if(new_unscaling_method == "MeanStandardDeviation")
    {
        set_unscaling_method(MeanStandardDeviation);
    }
    else if(new_unscaling_method == "MinimumMaximum")
    {
        set_unscaling_method(MinimumMaximum);
    }
    else if(new_unscaling_method == "Logarithmic")
    {
        set_unscaling_method(Logarithmic);
    }
    else
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "void set_unscaling_method(const string&) method.\n"
               << "Unknown unscaling method: " << new_unscaling_method << ".\n";

        throw logic_error(buffer.str());
    }
}


/// Sets a new display value.
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void UnscalingLayer::set_display(const bool& new_display)
{
    display = new_display;
}


/// Checks whether the outptus from the unscaling layer are inside the range defined by the minimums and maximum values.
/// It displays a warning message if they are outside.
/// @param outputs Set of outptus from the unscaling layer.

void UnscalingLayer::check_range(const Tensor<type, 1>& outputs) const
{
    const Index neurons_number = get_neurons_number();

#ifdef __OPENNN_DEBUG__

    const Index size = outputs.size();

    if(size != neurons_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "void check_range(const Tensor<type, 1>&) const method.\n"
               << "Size of outputs must be equal to number of unscaling neurons.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Check outputs

    if(display)
    {
        for(Index i = 0; i < neurons_number; i++)
        {
            if(outputs[i] < descriptives[i].minimum)
            {
                cout << "OpenNN Warning: UnscalingLayer class.\n"
                     << "void check_range(const Tensor<type, 1>&) const method.\n"
                     << "Output variable " << i << " is less than outputs.\n";
            }

            if(outputs[i] > descriptives[i].maximum)
            {
                cout << "OpenNN Warning: UnscalingLayer class.\n"
                     << "void check_range(const Tensor<type, 1>&) const method.\n"
                     << "Output variable " << i << " is greater than maximum.\n";
            }
        }
    }
}


/// Returns true if the number of unscaling neurons is zero, and false otherwise.

bool UnscalingLayer::is_empty() const
{
    const Index neurons_number = get_neurons_number();

    if(neurons_number == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/// Calculates the outputs from the unscaling layer for a given set of inputs to that layer.
/// @param inputs Set of inputs to the unscaling layer.

Tensor<type, 2> UnscalingLayer::calculate_outputs(const Tensor<type, 2>& inputs)
{

#ifdef __OPENNN_DEBUG__

    const Index neurons_number = get_neurons_number();

    const Index columns_number = inputs.dimension(1);

    if(columns_number != neurons_number)
    {
        ostringstream buffer;

        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "Tensor<type, 2> calculate_outputs(const Tensor<type, 2>&) const method.\n"
               << "Size must be equal to number of unscaling neurons.\n";

        throw logic_error(buffer.str());
    }

#endif

    // Unscale

    switch(unscaling_method)
    {
    case MinimumMaximum:
    {
        return calculate_minimum_maximum_outputs(inputs);
    }

    case MeanStandardDeviation:
    {

        return calculate_mean_standard_deviation_outputs(inputs);
    }

    case Logarithmic:
    {
        return calculate_logarithmic_outputs(inputs);
    }

    case NoUnscaling:
    {
        return inputs;
    }
    }

    return Tensor<type, 2>();
}


/// Calculates the outputs from the unscaling layer with the minimum and maximum method for a set of inputs.
/// @param inputs Vector of input values to the unscaling layer. The size must be equal to the number of unscaling neurons.

Tensor<type, 2> UnscalingLayer::calculate_minimum_maximum_outputs(const Tensor<type, 2>& inputs) const
{
    const Index points_number = inputs.dimension(0);
    const Index neurons_number = get_neurons_number();

    Tensor<type, 2> outputs(points_number, neurons_number);

    for(Index i = 0; i < points_number; i++)
    {
        for(Index j = 0; j < neurons_number; j++)
        {
            if(descriptives(j).maximum - descriptives(j).minimum < numeric_limits<type>::min())
            {
                if(display)
                {
                    cout << "OpenNN Warning: UnscalingLayer class.\n"
                         << "Tensor<type, 1> calculate_minimum_maximum_outputs(Tensor<type, 1>&) const method.\n"
                         << "Minimum and maximum values of output variable " << i << " are equal.\n"
                         << "Those outputs won't be unscaled.\n";
                }

                outputs(i,j) = 0;
            }
            else
            {
                outputs(i,j) = static_cast<type>(0.5)*(inputs(i,j) + 1)*(descriptives(j).maximum-descriptives(j).minimum) + descriptives(j).minimum;
            }
        }
    }

    return outputs;
}


/// Calculates the outputs from the unscaling layer with the mean and standard deviation method for a set of inputs.
/// @param inputs Vector of input values to the unscaling layer. The size must be equal to the number of unscaling neurons.

Tensor<type, 2> UnscalingLayer::calculate_mean_standard_deviation_outputs(const Tensor<type, 2>& inputs) const
{
    const Index points_number = inputs.dimension(0);
    const Index neurons_number = get_neurons_number();

    Tensor<type, 2> outputs(points_number, neurons_number);

    for(Index i = 0; i < points_number; i++)
    {
        for(Index j = 0; j < neurons_number; j++)
        {
            if(descriptives[j].standard_deviation < numeric_limits<type>::min())
            {
                if(display)
                {
                    cout << "OpenNN Warning: UnscalingLayer class.\n"
                         << "Tensor<type, 1> calculate_mean_standard_deviation_outputs(const Tensor<type, 1>&) const method.\n"
                         << "Standard deviation of output variable " << j << " is zero.\n"
                         << "Those outputs won't be unscaled.\n";
                }

                outputs(i,j) = 0;
            }
            else
            {
                outputs(i,j) = inputs(0,j)*descriptives[j].standard_deviation + descriptives[j].mean;
            }
        }
    }

    return outputs;
}


/// Calculates the outputs from the unscaling layer with the logarithmic method for a set of inputs.
/// @param inputs Vector of input values to the unscaling layer. The size must be equal to the number of unscaling neurons.

Tensor<type, 2> UnscalingLayer::calculate_logarithmic_outputs(const Tensor<type, 2>& inputs) const
{
    const Index points_number = inputs.dimension(0);

    const Index neurons_number = get_neurons_number();

    Tensor<type, 2> outputs(points_number, neurons_number);

    for(Index i = 0; i < points_number; i++)
    {
        for(Index j = 0; j < neurons_number; j++)
        {
            if(descriptives[j].maximum - descriptives[j].minimum < numeric_limits<type>::min())
            {
                if(display)
                {
                    cout << "OpenNN Warning: UnscalingLayer class.\n"
                         << "Tensor<type, 1> calculate_logarithmic_outputs(Tensor<type, 1>&) const method.\n"
                         << "Minimum and maximum values of output variable " << j << " are equal.\n"
                         << "Those outputs won't be unscaled.\n";
                }

                outputs(i,j) = 0;
            }
            else
            {
                outputs(i,j) = static_cast<type>(0.5)*(exp(inputs(i,j))+1)*(descriptives[j].maximum-descriptives[j].minimum) + descriptives[j].minimum;
            }
        }
    }

    return outputs;
}


/// Returns a string representation of the current unscaling layer object.

string UnscalingLayer::object_to_string() const
{
    ostringstream buffer;

    const Index neurons_number = get_neurons_number();

    buffer << "Unscaling layer\n";

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer << "Descriptives " << i+1 << ":\n"
               << "Minimum: " << descriptives[i].minimum << "\n"
               << "Maximum: " << descriptives[i].maximum << "\n"
               << "Mean: " << descriptives[i].mean << "\n"
               << "Standard deviation: " << descriptives[i].standard_deviation << "\n";
    }

    buffer << "Unscaling method: " << write_unscaling_method() << "\n";
    //<< "Display: " << display << "\n";

    return buffer.str();
}


/// Serializes this unscaling layer object into a TinyXML document->
/// Please read the OpenNN manual for more information about this.

tinyxml2::XMLDocument* UnscalingLayer::to_XML() const
{
    ostringstream buffer;

    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

    tinyxml2::XMLElement* unscaling_layer_element = document->NewElement("UnscalingLayer");

    document->InsertFirstChild(unscaling_layer_element);

    tinyxml2::XMLElement* element = nullptr;
    tinyxml2::XMLText* text = nullptr;

    const Index neurons_number = get_neurons_number();

    // Unscaling neurons number
    {
        element = document->NewElement("UnscalingNeuronsNumber");
        unscaling_layer_element->LinkEndChild(element);

        buffer.str("");
        buffer << neurons_number;

        text = document->NewText(buffer.str().c_str());
        element->LinkEndChild(text);
    }

    for(Index i = 0; i < neurons_number; i++)
    {
        tinyxml2::XMLElement* statistics_element = document->NewElement("Descriptives");
        statistics_element->SetAttribute("Index", int(i+1));

        unscaling_layer_element->LinkEndChild(statistics_element);

        // Minimum

        tinyxml2::XMLElement* minimum_element = document->NewElement("Minimum");
        statistics_element->LinkEndChild(minimum_element);

        buffer.str("");
        buffer << descriptives[i].minimum;

        tinyxml2::XMLText* minimum_text = document->NewText(buffer.str().c_str());
        minimum_element->LinkEndChild(minimum_text);

        // Maximum

        tinyxml2::XMLElement* maximum_element = document->NewElement("Maximum");
        statistics_element->LinkEndChild(maximum_element);

        buffer.str("");
        buffer << descriptives[i].maximum;

        tinyxml2::XMLText* maximum_text = document->NewText(buffer.str().c_str());
        maximum_element->LinkEndChild(maximum_text);

        // Mean

        tinyxml2::XMLElement* mean_element = document->NewElement("Mean");
        statistics_element->LinkEndChild(mean_element);

        buffer.str("");
        buffer << descriptives[i].mean;

        tinyxml2::XMLText* mean_text = document->NewText(buffer.str().c_str());
        mean_element->LinkEndChild(mean_text);

        // Standard deviation

        tinyxml2::XMLElement* standard_deviation_element = document->NewElement("StandardDeviation");
        statistics_element->LinkEndChild(standard_deviation_element);

        buffer.str("");
        buffer << descriptives[i].standard_deviation;

        tinyxml2::XMLText* standard_deviation_text = document->NewText(buffer.str().c_str());
        standard_deviation_element->LinkEndChild(standard_deviation_text);
    }

    // Unscaling method
    {
        element = document->NewElement("UnscalingMethod");
        unscaling_layer_element->LinkEndChild(element);

        text = document->NewText(write_unscaling_method().c_str());
        element->LinkEndChild(text);
    }

    // Display
    //   {
    //      element = document->NewElement("Display");
    //      unscaling_layer_element->LinkEndChild(element);

    //      buffer.str("");
    //      buffer << display;

    //      text = document->NewText(buffer.str().c_str());
    //      element->LinkEndChild(text);
    //   }

    return document;
}


/// Serializes the unscaling layer object into a XML document of the TinyXML library without keep the DOM tree in memory.
/// See the OpenNN manual for more information about the format of this document.

void UnscalingLayer::write_XML(tinyxml2::XMLPrinter& file_stream) const
{
    ostringstream buffer;

    const Index neurons_number = get_neurons_number();

    // Unscaling layer

    file_stream.OpenElement("UnscalingLayer");

    // Unscaling neurons number

    file_stream.OpenElement("UnscalingNeuronsNumber");

    buffer.str("");
    buffer << neurons_number;

    file_stream.PushText(buffer.str().c_str());

    file_stream.CloseElement();

    // Descriptives

    for(Index i = 0; i < neurons_number; i++)
    {
        file_stream.OpenElement("Descriptives");

        file_stream.PushAttribute("Index", int(i+1));

        // Minimum

        file_stream.OpenElement("Minimum");

        buffer.str("");
        buffer << descriptives[i].minimum;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();

        // Maximum

        file_stream.OpenElement("Maximum");

        buffer.str("");
        buffer << descriptives[i].maximum;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();

        // Mean

        file_stream.OpenElement("Mean");

        buffer.str("");
        buffer << descriptives[i].mean;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();

        // Standard deviation

        file_stream.OpenElement("StandardDeviation");

        buffer.str("");
        buffer << descriptives[i].standard_deviation;

        file_stream.PushText(buffer.str().c_str());

        file_stream.CloseElement();


        file_stream.CloseElement();
    }

    // Unscaling method

    file_stream.OpenElement("UnscalingMethod");

    file_stream.PushText(write_unscaling_method().c_str());

    file_stream.CloseElement();

    // Unscaling layer (end tag)

    file_stream.CloseElement();
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this unscaling layer object.
/// @param document XML document containing the member data.

void UnscalingLayer::from_XML(const tinyxml2::XMLDocument& document)
{
    ostringstream buffer;

    const tinyxml2::XMLElement* root_element = document.FirstChildElement("UnscalingLayer");

    if(!root_element)
    {
        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Unscaling layer element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    // Unscaling neurons number

    const tinyxml2::XMLElement* neurons_number_element = root_element->FirstChildElement("UnscalingNeuronsNumber");

    if(!neurons_number_element)
    {
        buffer << "OpenNN Exception: UnscalingLayer class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Unscaling neurons number element is nullptr.\n";

        throw logic_error(buffer.str());
    }

    const Index neurons_number = static_cast<Index>(atoi(neurons_number_element->GetText()));

    set(neurons_number);

    unsigned index = 0; // Index does not work

    const tinyxml2::XMLElement* start_element = neurons_number_element;

    for(Index i = 0; i < neurons_number; i++)
    {
        const tinyxml2::XMLElement* descriptives_element = start_element->NextSiblingElement("Descriptives");
        start_element = descriptives_element;

        if(!descriptives_element)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Descriptives of unscaling neuron " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        descriptives_element->QueryUnsignedAttribute("Index", &index);

        if(index != i+1)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Index " << index << " is not correct.\n";

            throw logic_error(buffer.str());
        }

        // Minimum

        const tinyxml2::XMLElement* minimum_element = descriptives_element->FirstChildElement("Minimum");

        if(!minimum_element)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Minimum element " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        if(minimum_element->GetText())
        {
            descriptives(i).minimum = static_cast<type>(atof(minimum_element->GetText()));
        }

        // Maximum

        const tinyxml2::XMLElement* maximum_element = descriptives_element->FirstChildElement("Maximum");

        if(!maximum_element)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Maximum element " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        if(maximum_element->GetText())
        {
            descriptives(i).maximum = static_cast<type>(atof(maximum_element->GetText()));
        }

        // Mean

        const tinyxml2::XMLElement* mean_element = descriptives_element->FirstChildElement("Mean");

        if(!mean_element)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Mean element " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        if(mean_element->GetText())
        {
            descriptives(i).mean = static_cast<type>(atof(mean_element->GetText()));
        }

        // Standard deviation

        const tinyxml2::XMLElement* standard_deviation_element = descriptives_element->FirstChildElement("StandardDeviation");

        if(!standard_deviation_element)
        {
            buffer << "OpenNN Exception: UnscalingLayer class.\n"
                   << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                   << "Standard deviation element " << i+1 << " is nullptr.\n";

            throw logic_error(buffer.str());
        }

        if(standard_deviation_element->GetText())
        {
            descriptives(i).standard_deviation = static_cast<type>(atof(standard_deviation_element->GetText()));
        }

        // Unscaling method

        const tinyxml2::XMLElement* unscaling_method_element = root_element->FirstChildElement("UnscalingMethod");

        if(unscaling_method_element)
        {
            const string new_method = unscaling_method_element->GetText();

            try
            {
                set_unscaling_method(new_method);
            }
            catch(const logic_error& e)
            {
                cerr << e.what() << endl;
            }
        }
    }

    // Display

    const tinyxml2::XMLElement* element = root_element->FirstChildElement("Display");

    if(element)
    {
        string new_display_string = element->GetText();

        try
        {
            set_display(new_display_string != "0");
        }
        catch(const logic_error& e)
        {
            cerr << e.what() << endl;
        }
    }
}


/// Returns a string with the expression of the unscaling process with the none method.
/// @param inputs_names Name of inputs to the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @param outputs_names Name of outputs from the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @todo

string UnscalingLayer::write_none_expression(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    ostringstream buffer;

    for (Index i = 0; i < outputs_names.size(); i++)
    {
    buffer << outputs_names(i) << " = " << inputs_names(i) << ";\n";
    }

    return buffer.str();
}


/// @todo

string UnscalingLayer::write_none_expression_php(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    ostringstream buffer;

    buffer.str("");

//    buffer << outputs_names.vector_to_string(',') << " = " << inputs_names.vector_to_string(',') << ";\n";

    return buffer.str();
}


// string write_minimum_maximum_expression(const Tensor<string, 1>&, const Tensor<string, 1>&) const method

/// Returns a string with the expression of the unscaling process with the minimum and maximum method.
/// @param inputs_names Name of inputs to the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @param outputs_names Name of outputs from the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.

string UnscalingLayer::write_minimum_maximum_expression(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer << outputs_names[i] << " = " <<
        "0.5*(" << inputs_names[i] << "+1)*(" << descriptives[i].maximum << "-(" << descriptives[i].minimum << "))+(" << descriptives[i].minimum << ");\n";

        expressions[i] = buffer.str();
    }

//    buffer.str("");
    /*
        if(outputs_names.size() > 1)
        {
            buffer << " (" << outputs_names.vector_to_string(',') << ") = (" << expressions.vector_to_string(',') << ");\n";
        }
        else
        {
            buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
        }
    */
    return buffer.str();
}


string UnscalingLayer::write_minimum_maximum_expression_php(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer << "0.5*(" << inputs_names[i] << "+1.0)*(" << descriptives[i].maximum << "-" << descriptives[i].minimum << ")+" << descriptives[i].minimum;

        expressions[i] = buffer.str();
    }

    buffer.str("");
    /*
        if(outputs_names.size() > 1)
        {
            buffer << " (" << outputs_names.vector_to_string(',') << ") = (" << expressions.vector_to_string(',') << ");\n";
        }
        else
        {
            buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
        }
    */
    return buffer.str();
}


// string write_mean_standard_deviation_expression(const Tensor<string, 1>&, const Tensor<string, 1>&) const method

/// Returns a string with the expression of the unscaling process with the mean and standard deviation method.
/// @param inputs_names Name of inputs to the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @param outputs_names Name of outputs from the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.

string UnscalingLayer::write_mean_standard_deviation_expression(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer << outputs_names(i) << " = (" <<
        descriptives[i].mean << ")+(" << descriptives[i].standard_deviation << ")*" << inputs_names[i] << ";\n";

        expressions[i] = buffer.str();
    }

//    buffer.str("");
    /*
        if(outputs_names.size() > 1)
        {
            buffer << " (" << outputs_names.vector_to_string(',') << ") = (" << expressions.vector_to_string(',') << ");\n";
        }
        else
        {
            buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
        }
    */
    return buffer.str();
}


string UnscalingLayer::write_mean_standard_deviation_expression_php(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer <<   descriptives[i].mean << "+" << descriptives[i].standard_deviation << "*" << inputs_names[i];

        expressions[i] = buffer.str();
    }

    buffer.str("");
    /*
        buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
    */
    return buffer.str();
}


/// Returns a string with the expression of the unscaling process with the mean and standard deviation method.
/// @param inputs_names Name of inputs to the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @param outputs_names Name of outputs from the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.

string UnscalingLayer::write_logarithmic_expression(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer << outputs_names(i) << " = " <<
                  "0.5*exp(" << inputs_names[i] << "-1)*(" << descriptives[i].maximum << "-(" << descriptives[i].minimum << "))+(" << descriptives[i].minimum << ");\n";

        expressions[i] = buffer.str();
    }

//    buffer.str("");
    /*
        if(outputs_names.size() > 1)
        {
            buffer << " (" << outputs_names.vector_to_string(',') << ") = (" << expressions.vector_to_string(',') << ");\n";
        }
        else
        {
            buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
        }
    */
    return buffer.str();
}


string UnscalingLayer::write_logarithmic_expression_php(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    Tensor<string, 1> expressions(neurons_number);

    for(Index i = 0; i < neurons_number; i++)
    {
        buffer.str("");
        buffer << "0.5*exp(" << inputs_names[i] << "-1)*(" << descriptives[i].maximum << "-" << descriptives[i].minimum << ")+" << descriptives[i].minimum;

        expressions[i] = buffer.str();
    }

    buffer.str("");
    /*
        buffer << outputs_names.vector_to_string(',') << " = (" << expressions.vector_to_string(',') << ");\n";
    */
    return buffer.str();
}


// string write_expression(const Tensor<string, 1>&, const Tensor<string, 1>&) const method

/// Returns a string with the expression of the unscaling process in this layer.
/// @param inputs_names Name of inputs to the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.
/// @param outputs_names Name of outputs from the unscaling layer. The size of this vector must be equal to the number of unscaling neurons.

string UnscalingLayer::write_expression(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    switch(unscaling_method)
    {
    case NoUnscaling:
    {
        return write_none_expression(inputs_names, outputs_names);
    }

    case MinimumMaximum:
    {
        return write_minimum_maximum_expression(inputs_names, outputs_names);
    }

    case MeanStandardDeviation:
    {
        return write_mean_standard_deviation_expression(inputs_names, outputs_names);
    }

    case Logarithmic:
    {
        return write_logarithmic_expression(inputs_names, outputs_names);
    }
    }

    ostringstream buffer;

    buffer << "OpenNN Exception: UnscalingLayer class.\n"
           << "string write_expression(const Tensor<string, 1>&, const Tensor<string, 1>&) const method.\n"
           << "Unknown unscaling method.\n";

    throw logic_error(buffer.str());
}


string UnscalingLayer::write_expression_php(const Tensor<string, 1>& inputs_names, const Tensor<string, 1>& outputs_names) const
{
    switch(unscaling_method)
    {
    case NoUnscaling:
    {
        return write_none_expression_php(inputs_names, outputs_names);
    }

    case MinimumMaximum:
    {
        return write_minimum_maximum_expression_php(inputs_names, outputs_names);
    }

    case MeanStandardDeviation:
    {
        return write_mean_standard_deviation_expression_php(inputs_names, outputs_names);
    }

    case Logarithmic:
    {
        return write_logarithmic_expression_php(inputs_names, outputs_names);
    }

    }

    ostringstream buffer;

    buffer << "OpenNN Exception: UnscalingLayer class.\n"
           << "string write_expression_php(const Tensor<string, 1>&, const Tensor<string, 1>&) const method.\n"
           << "Unknown unscaling method.\n";

    throw logic_error(buffer.str());
}

//string UnscalingLayer::write_expression_c() const
//{
//    const Index neurons_number = get_neurons_number();

//    ostringstream buffer;

//    buffer << "vector<float> " << layer_name << "(const vector<float>& inputs)\n{" << endl;

//    buffer << "\tvector<float> outputs(" << neurons_number << ");\n" << endl;

//    for(Index i = 0; i < neurons_number; i++)
//    {
//        buffer << "\toutputs[" << i << "] = inputs[" << i << "];" << endl;
//    }

//    buffer << "\n\treturn outputs;\n}" << endl;

//    return buffer.str();
//}

string UnscalingLayer::write_expression_c() const
{
    const Index neurons_number = get_neurons_number();

    ostringstream buffer;

    buffer.precision(10);

    for(Index i = 0; i < neurons_number; i++)
    {
//        if(unscaling_methods(i) == NoUnscaling)
//        {
//            buffer << "\toutputs[" << i << "] = inputs[" << i << "];" << endl;
//        }
//        else if(unscaling_methods(i) == MinimumMaximum)
//        {
//            buffer << "\toutputs[" << i << "] = (inputs[" << i << "])*(" <<  descriptives(i).maximum << "-" << descriptives(i).maximum << ")+" << descriptives.minimum()<< endl;
//        }
//        else if(unscaling_methods(i) == MeanStandardDeviation)
//        {
//            buffer << "\toutputs[" << i << "] = (inputs[" << i << "] -" <<  descriptives(i).mean << ")/" << descriptives(i).standard_deviation << " ;" << endl;
//        }
//        else if(unscaling_methods(i) == StandardDeviation)
//        {
//            buffer << "\toutputs[" << i << "] = inputs[" << i << "]/" << descriptives(i).standard_deviation << " ;" << endl;
//        }
//        else
//        {
//            ostringstream buffer;

//            buffer << "OpenNN Exception: ScalingLayer class.\n"
//                   << "string write_expression() const method.\n"
//                   << "Unknown inputs scaling method.\n";

//            throw logic_error(buffer.str());
//        }
    }

    return buffer.str();
}




}


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
