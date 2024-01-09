// Datastructures.hh
//
// Student name: Lassi Lappalainen
// Student email: lassi.lappalainen@tuni.fi
// Student number: 150390123

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

#include <set>
#include <map>
#include <unordered_set>
#include <queue>
#include <list>

#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
struct Connection;
// Type for a distance (in arbitrary units)
using Distance = int;

using Path = std::vector<Connection>;
using PathWithDist = std::vector<std::pair<Connection,Distance>>;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

struct Connection
{
    AffiliationID aff1 = NO_AFFILIATION;
    AffiliationID aff2 = NO_AFFILIATION;
    Weight weight = NO_WEIGHT;
    bool operator==(const Connection& c1) const{
        return (aff1==c1.aff1) && (aff2==c1.aff2) && (weight==c1.weight);
    }
};
const Connection NO_CONNECTION{NO_AFFILIATION,NO_AFFILIATION,NO_WEIGHT};


// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: This function simply returns the size.
    // Since getting the size of a map is a constant-time operation in C++, the
    // function has O(1) complexity.
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function clears multiple data structures.
    // The complexity depends on the total number of elements in these structures.
    // Each clear() operation is linear in the size of the structure.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Returns all elements in all_affiliation_ids,
    // which is a vector. Copying all elements of a vector has linear complexity in the size of the vector.
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance:  O(log(n))
    // Short rationale for estimate: Involves a map lookup and several insertions into different data structures.
    // Map lookups and insertions generally have logarithmic complexity.
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: This function performs a lookup in affiliations_map,
    // a map data structure. Map lookups have logarithmic complexity.
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate:  Similar to get_affiliation_name, this function
    // performs a map lookup in affiliations_map. Map lookups have logarithmic complexity.
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: This function returns affiliations in alphabetical order.
    // It sorts sorted_affiliations and cache the results in a vector.
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Similar to previous, it sorts sorted_by_distance
    // and caches the result.
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Involves a lookup in coord_to_affiliation_map, which is a multimap.
    // The lookup complexity in a multimap is logarithmic.
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Involves map lookups and insertions, as well as
    // updating sorted structures. Each of these operations has logarithmic complexity.
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate:  Involves a map lookup and iterating over an
    // affiliations vector to update structures. The map lookup is O(log n), and
    // iterating over the affiliations vector adds linear complexity,
    // leading to a combined O(n*log(n)) complexity.
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID> & affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates over all elements in publications_map and constructs a vector of publication IDs.
    // Iteration over a map and copying each element into a vector has linear complexity in the number of elements.
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Perform a lookup in publications_map,
    // which is a map. Lookup operations in a map typically have logarithmic complexity.
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Similar to 'get_publication_name'
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: Involves a lookup in publications_map and then returns the affiliations vector.
    // The complexity is primarily due to the map lookup, which is logarithmic.
    // However, the function may also be iterating over the affiliations vector
    // to construct the return value, which could add linear complexity depending on the implementation.
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate:  Involves two map lookups in publications_map and
    // checks for existing references. Map lookups have logarithmic complexity.
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function involves a lookup in publications_map
    // to find the publication and then returns its references.
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(log(n))
    // Short rationale for estimate: Performs two map lookups (in affiliations_map and publications_map),
    // both having logarithmic complexity.
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates over all publications in publications_map
    // to find those associated with a given affiliation ID, which has linear complexity in the size of the map.
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates through all publications in publications_map
    // to find the parent of a given publication, which is a linear operation in the number of publications.
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Finds the given affiliation in publications_by_affiliation_and_year
    // and iterates over publications from the specified year onwards.
    // The complexity is due to both the map lookup and the iteration over a potentially large number of publications.
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: Iterates through a chain of references
    // and performs a map lookup in backward_references. The complexity is due
    // to the potential length of the reference chain and the logarithmic complexity of each map lookup.
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function implements a depth-first search (DFS)
    // through the publication references. DFS has a complexity of O(n) in the worst case,
    // where n is the number of nodes (publications) in the graph. This is because it may potentially visit every node in the graph.
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: The function calculates distances for each affiliation and then sorts these distances.
    // Calculating distances for all affiliations is O(n), and sorting these distances is O(n log n).
    // The overall complexity is dominated by the sorting operation.
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function involves finding and removing an affiliation
    // from several data structures (affiliations_map, sorted_affiliations, etc.).
    // The complexity mainly comes from potentially having to iterate over all
    // elements in these structures to remove references to the affiliation.
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: The function builds paths from the given publications to their respective roots,
    // which is an O(n) operation for each publication.
    // It then searches for a common parent in these paths, which can be
    // another O(n) operation, leading to a quadratic O(n^2) complexity in the worst case.
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function involves removing a publication
    // from publications_map (which is an O(log n) operation) and then iterating
    // over all publications to remove references to the publication being deleted.
    // The iteration over all publications dominates the complexity, making it linear in the number of publications.
    bool remove_publication(PublicationID publicationid);

    // PRG 2 functions:

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterates through all publications (P) and then through the affiliations (A)
    // in these publications to build the list of connections. Complexity is linear with the number of publications
    // and affiliations involved.
    std::vector<Connection> get_connected_affiliations(AffiliationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Iterates through each pair of affiliations (A) in the shared_publications_count map.
    // Since it potentially considers every pair, the complexity is quadratic in the number of affiliations.
    std::vector<Connection> get_all_connections();

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Uses Breadth-First Search (BFS), where A is the number of affiliations
    // and E is the number of edges in the adjacency list. In the worst case, the function will visit every
    // affiliation and edge once, leading to linear complexity with respect to the total number of affiliations and edges.
    Path get_any_path(AffiliationID source, AffiliationID target);

    // PRG2 optional functions

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_with_least_affiliations(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    Path get_path_of_least_friction(AffiliationID source, AffiliationID target);

    // Estimate of performance:
    // Short rationale for estimate:
    PathWithDist get_shortest_path(AffiliationID source, AffiliationID target);


private:


    // These can be added/changed for the project

    // Struct for affiliations info
    struct Affiliation {
        Name name;
        Coord location;
    };

    // These struct's compare distances and alphabets (for optimizing)
    struct DistanceComparator {
        std::unordered_map<AffiliationID, Affiliation>& map_ref;

        DistanceComparator(std::unordered_map<AffiliationID, Affiliation>& map)
            : map_ref(map) {}

        bool operator()(const AffiliationID& a, const AffiliationID& b) const {
            const auto& coordA = map_ref.at(a).location;
            const auto& coordB = map_ref.at(b).location;
            double distA = coordA.x * coordA.x + coordA.y * coordA.y;
            double distB = coordB.x * coordB.x + coordB.y * coordB.y;

            return distA < distB || (distA == distB && coordA.y < coordB.y);
        }
    };

    std::set<AffiliationID, DistanceComparator> sorted_by_distance;

    struct AffiliationComparator {
        std::unordered_map<AffiliationID, Affiliation>& map_ref;

        AffiliationComparator(std::unordered_map<AffiliationID, Affiliation>& map)
            : map_ref(map) {}

        bool operator()(const AffiliationID& a, const AffiliationID& b) const {
            return map_ref.at(a).name < map_ref.at(b).name;
        }
    };

    std::set<AffiliationID, AffiliationComparator> sorted_affiliations;

    // caches for faster/less commands needed for ordering distance and alph.
    std::vector<AffiliationID> alphabetical_cache;
    bool is_alphabetical_cache_valid = false;
    std::vector<AffiliationID> distance_cache;
    bool is_distance_cache_valid = false;
    std::unordered_multimap<Coord, AffiliationID, CoordHash> coord_to_affiliation_map;

    // Unordered map, which uses ID for affiliations and the struct
    std::unordered_map<AffiliationID, Affiliation> affiliations_map;

    // Additional datastructures for optimizing
    std::unordered_map<AffiliationID, std::map<Year, std::vector<PublicationID>>> publications_by_affiliation_and_year;
    std::multimap<Coord, AffiliationID> coord_affiliation_multimap;
    std::vector<AffiliationID> all_affiliation_ids;

    // Struct for publication info
    struct Publication {
        PublicationID id;
        Name title;
        Year year;
        std::vector<PublicationID> references;
        std::vector<AffiliationID> affiliations;
    };

    // Unordered map, where ID works as key for publications struct and references vector
    std::unordered_map<PublicationID, Publication> publications_map;
    std::unordered_map<PublicationID, std::vector<PublicationID>> backward_references;


    // PRG2

    struct ConnectionComparator {
        bool operator()(const Connection& c1, const Connection& c2) const {
            if (c1.aff1 < c2.aff1) return true;
            if (c1.aff1 > c2.aff1) return false;
            return c1.aff2 < c2.aff2;
        }
    };

    std::unordered_map<AffiliationID, std::vector<AffiliationID>> adjacency_list;

    void build_adjacency_list() {
        adjacency_list.clear();
        for (const auto& pubPair : publications_map) {
            const auto& publication = pubPair.second;
            for (size_t i = 0; i < publication.affiliations.size(); ++i) {
                for (size_t j = i + 1; j < publication.affiliations.size(); ++j) {
                    adjacency_list[publication.affiliations[i]].push_back(publication.affiliations[j]);
                    adjacency_list[publication.affiliations[j]].push_back(publication.affiliations[i]);
                }
            }
        }
    }

    std::unordered_map<AffiliationID, std::unordered_map<AffiliationID, int>> shared_publications_count;

    struct PathInfo {
        double totalFriction;
        int minWeight;
        int pathLength;
        AffiliationID previous;

        PathInfo(double totalFriction = std::numeric_limits<double>::max(),
                 int minWeight = std::numeric_limits<int>::max(),
                 int pathLength = 0,
                 AffiliationID previous = "")
            : totalFriction(totalFriction), minWeight(minWeight), pathLength(pathLength), previous(previous) {}
    };

    using Graph = std::unordered_map<AffiliationID, std::vector<Connection>>;


};

#endif // DATASTRUCTURES_HH
