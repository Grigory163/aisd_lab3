// aisd_lab3.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.
//В глубину Беллмана - Форда



#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

template<typename Vertex, typename Distance = double>
class Graph
{
public:
	struct Edge
	{
		Vertex source;
		Vertex destination;
		Distance weight;
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

}; 