#pragma once

#include <random>
#include <ctime>
#include <memory>

namespace Neuro
{

	struct Activation;
	struct McCulloughPitts;

	template<typename T>
	struct Settings
	{ };

	template<>
	struct Settings<McCulloughPitts>
	{
		double threshold;
	};

	struct WeightSimple
	{
		double w = 0.0;
	};

	template<typename Cell, typename Weight>
	class Link
	{
	public:
		std::shared_ptr<Cell>       cell() const { return m_cell; }
	private:
		std::shared_ptr<Cell>       m_cell;
		std::shared_ptr<Weight>     m_weight;
	};

	struct Activation
	{
	public:
		Activation() { }
	protected:
		virtual double response(double input) const { return input; }
		//virtual void configure(const std::shared_ptr<const Settings<X> > settings) { }
	};

	struct McCulloughPitts : public Activation
	{
		//McCulloughPitts(const std::shared_ptr<const Settings<McCulloughPitts> > settings)
		//{
		//	threshold = settings->threshold;
		//}

	protected:
		virtual double response(double input) const { return input >= threshold ? 1.0 : 0.0; }
		double threshold = 0.0;
	};

	struct Logistic : public Activation
	{
	protected:
		virtual double response(double input) const { return 1.0 / (1.0 + exp(-input)); }
	};

	template<typename A = Activation>
	class Neuron : public A
	{
		typedef std::shared_ptr<Link<Neuron, WeightSimple> >    sp_link_t;
		typedef std::vector<sp_link_t>                          vec_links_t;

	public:
		Neuron() {}

		void initialise(double initialState)
		{
			m_internalState = initialState;
		//	configure(m_settings);
		}

		void update()
		{
			for (auto link : m_incomingLinks)
			{
				m_internalState += link->cell()->output();
			}
		}

		double output() const
		{
			return response(m_internalState);
		}

	private:
		vec_links_t                     m_incomingLinks;
		double                          m_internalState;
		std::shared_ptr<Settings<A>>    m_settings;
	};

	class RNG_simple
	{
	public:
		RNG_simple()
		{
			time_t getTime = time(NULL);
			unsigned long long loc_seed = (getTime) % 100000;
			m_mersenne_64.seed(loc_seed);
		}

		double uni_01()
		{
			std::uniform_real_distribution<double>  uniform(0.0, 1.0);
			return uniform(m_mersenne_64);
		}

	private:
		std::mt19937_64                        m_mersenne_64;
	};
}