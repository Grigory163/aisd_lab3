// aisd_lab3.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.
//В глубину Беллмана - Форда



#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

template<typename Vertex, typename Distance = double>
class Graph
{
public:
	struct Edge
	{
		Vertex source;
		Vertex destination;
		Distance weight;
		bool operator==(const Edge& other) const
		{
			return (source == other.source) && (destination == other.destination) && (weight == other.weight);
		}
	};
private:
	std::vector<Vertex> _vertices;
	std::vector<Edge> _edges;
public:
	//проверка-добавление-удаление вершин

	bool has_vertex(const Vertex& v) const
	{
		return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
	}

	void add_vertex(const Vertex& v)
	{
		if (!has_vertex(v))
			_vertices.push_back(v);
	}

	bool remove_vertex(const Vertex& v)
	{
		auto it = std::find(_vertices.begin(), _vertices.end(), v);
		if (it == _vertices.end())
			return false;

		_vertices.erase(it);

		auto edges_it = _edges.begin();
		while (edges_it != _edges.end())
		{
			if (edges_it->source == v || edges_it->destination == v)
			{
				edges_it = _edges.erase(edges_it);
			}
			else
				edges_it++;
		}
		return true;
	}

	std::vector<Vertex> vertices() const
	{
		return _vertices;
	}

	//проверка-добавление-удаление ребер

	bool has_edge(const Vertex& _from, const Vertex& _to) const
	{
		for (const auto& edge : _edges)
		{
			if (edge.source == _from && edge.destination == _to)
				return true;
		}
		return false;
	}

	bool has_edge(const Edge& e) const // с учетом расстояния
	{
		return std::find(_edges.begin(), _edges.end(), e) != _edges.end();
	}

	void add_edge(const Vertex& from, const Vertex& to, const Distance& d)
	{
		if (!has_edge({ from, to, d }))
			_edges.push_back({ from, to, d });
	}

	bool remove_edge(const Vertex& from, const Vertex& to)
	{
		if (!has_edge(from, to))
			return false;

		for (auto it = _edges.begin(); it != _edges.end();)
		{
			if (it->source == from && it->destination == to)
			{
				it = _edges.erase(it);
			}
			else
				it++;
		}
		return true;
	}

	bool remove_edge(const Edge& e)// с учетом расстояния
	{
		auto it = std::find(_edges.begin(), _edges.end(), e);
		if (it == _edges.end())
			return false;

		_edges.erase(it);

		return true;
	}

	//получение всех ребер, выходящих из вершины

	std::vector<Edge> edges(const Vertex& vertex)
	{
		std::vector<Edge> res_edges;
		for (auto& edge : _edges)
		{
			if (edge.source == vertex)
				res_edges.push_back(edge);
		}
		return res_edges;
	}

	size_t order() const
	{
		return _vertices.size();
	}


	size_t degree(const Vertex& v) const
	{
		size_t count = 0;
		for (auto& edge : _edges)
		{
			if (edge.source == v || edge.destination == v)
				count++;
		}
		return count;
	}

	//поиск кратчайшего пути

	std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const
	{
		std::vector<Distance> distance(_vertices.size(), std::numeric_limits<Distance>::max());
		std::vector<Vertex> predecessor(_vertices.size(), Vertex());

		distance[std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), from))] = 0;

		for (size_t i = 0; i < _vertices.size() - 1; ++i)
		{
			for (const auto& edge : _edges)
			{
				size_t u = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), edge.source));
				size_t v = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), edge.destination));
				Distance weight = edge.weight;

				if (distance[u] + weight < distance[v])
				{
					distance[v] = distance[u] + weight;
					predecessor[v] = edge.source;
				}
			}
		}

		for (const auto& edge : _edges)
		{
			size_t u = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), edge.source));
			size_t v = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), edge.destination));
			Distance weight = edge.weight;

			if (distance[u] + weight < distance[v])
			{
				// Negative cycle detected
				return {}; // Return an empty path
			}
		}

		std::vector<Edge> path;
		size_t current = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), to));
		while (predecessor[current] != Vertex())
		{
			Vertex pred = predecessor[current];
			auto it = std::find_if(_edges.begin(), _edges.end(), [pred, current, this](const Edge& edge) {
				return edge.source == pred && edge.destination == this->_vertices[current];
				});
			if (it != _edges.end())
			{
				path.push_back(*it);
				current = std::distance(_vertices.begin(), std::find(_vertices.begin(), _vertices.end(), pred));
			}
		}

		std::reverse(path.begin(), path.end());
		return path;
	}
	// обход 
	std::vector<Vertex> walk(const Vertex& start_vertex) const
	{
		std::vector<Vertex> visited_vertices;
		std::unordered_set<Vertex> visited_set;
		walkDFS(start_vertex, visited_vertices, visited_set);
		return visited_vertices;
	}

	void walkDFS(const Vertex& current_vertex, std::vector<Vertex>& visited_vertices, std::unordered_set<Vertex>& visited_set) const
	{
		visited_vertices.push_back(current_vertex);
		visited_set.insert(current_vertex);

		for (const auto& edge : _edges)
		{
			if (edge.source == current_vertex && visited_set.find(edge.destination) == visited_set.end())
			{
				walkDFS(edge.destination, visited_vertices, visited_set);
			}
		}
	}
}; 