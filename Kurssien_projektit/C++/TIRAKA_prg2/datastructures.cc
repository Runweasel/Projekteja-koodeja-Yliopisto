// Datastructures.cc
//
// Student name: Lassi Lappalainen
// Student email: lassi.lappalainen@tuni.fi
// Student number: 150390123

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <set>
#include <map>
#include <unordered_set>
#include <queue>
#include <list>
#include <iostream>

using namespace std;

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
    : sorted_by_distance(DistanceComparator(affiliations_map)),
      sorted_affiliations(AffiliationComparator(affiliations_map)) {
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return affiliations_map.size();
}

void Datastructures::clear_all()
{
    // Clearing all affiliation related data
    affiliations_map.clear();
    sorted_affiliations.clear();
    sorted_by_distance.clear();
    coord_to_affiliation_map.clear();
    all_affiliation_ids.clear();
    is_alphabetical_cache_valid = false;
    is_distance_cache_valid = false;
    alphabetical_cache.clear();
    distance_cache.clear();

    // Clearing all publication related data
    publications_map.clear();
    backward_references.clear();
    publications_by_affiliation_and_year.clear();

    // Clearing data structures added for PRG2
    shared_publications_count.clear();  // Clearing shared publications count
    adjacency_list.clear();  // If necessary, clear adjacency list

    // Add clear statements for any other data structures you might have added
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    return all_affiliation_ids;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{

    if (affiliations_map.find(id) != affiliations_map.end()) {
        return false;
    }

    affiliations_map.emplace(id, Affiliation{name, xy});
    sorted_affiliations.insert(id);
    sorted_by_distance.insert(id);
    all_affiliation_ids.emplace_back(id);


    is_alphabetical_cache_valid = false;
    is_distance_cache_valid = false;
    coord_to_affiliation_map.emplace(xy, id);

    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto it = affiliations_map.find(id);
    if (it != affiliations_map.end()) {
        return it->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto it = affiliations_map.find(id);
    if (it != affiliations_map.end()) {
        return it->second.location;
    }
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    if (!is_alphabetical_cache_valid) {
        alphabetical_cache.clear();
        for (const auto& id : sorted_affiliations) {
            alphabetical_cache.push_back(id);
        }
        is_alphabetical_cache_valid = true;
    }
    return alphabetical_cache;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    if (!is_distance_cache_valid) {
        distance_cache.clear();
        for (const auto& id : sorted_by_distance) {
            distance_cache.push_back(id);
        }
        is_distance_cache_valid = true;
    }
    return distance_cache;
}


AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto range = coord_to_affiliation_map.equal_range(xy);
    if (range.first != coord_to_affiliation_map.end()) {
        return range.first->second;
    }
    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = affiliations_map.find(id);
    if (it != affiliations_map.end()) {
        sorted_by_distance.erase(id);

        auto old_range = coord_to_affiliation_map.equal_range(it->second.location);
        for (auto i = old_range.first; i != old_range.second; ) {
            if (i->second == id) {
                i = coord_to_affiliation_map.erase(i);
            } else {
                ++i;
            }
        }

        it->second.location = newcoord;

        coord_to_affiliation_map.emplace(newcoord, id);

        sorted_by_distance.insert(id);

        is_distance_cache_valid = false;

        return true;
    }
    return false;
}


bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const vector<AffiliationID> &affiliations)
{
    if (publications_map.find(id) != publications_map.end()) {
        return false;
    }

    // Lisää julkaisu
    backward_references[id] = vector<PublicationID>();
    publications_map.emplace(id, Publication{id, name, year, {}, affiliations});

    for (const auto& affiliation_id : affiliations) {
        publications_by_affiliation_and_year[affiliation_id][year].push_back(id);
    }

    // Päivitä shared_publications_count
    for (size_t i = 0; i < affiliations.size(); ++i) {
        for (size_t j = i + 1; j < affiliations.size(); ++j) {
            shared_publications_count[affiliations[i]][affiliations[j]]++;
            shared_publications_count[affiliations[j]][affiliations[i]]++;

            // Päivitä adjacency_list
            adjacency_list[affiliations[i]].push_back(affiliations[j]);
            adjacency_list[affiliations[j]].push_back(affiliations[i]);
        }
    }

    return true;
}



std::vector<PublicationID> Datastructures::all_publications()
{
    vector<PublicationID> publication_ids;
    for (const auto& publication_pair : publications_map) {
        publication_ids.push_back(publication_pair.first);
    }
    return publication_ids;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto it = publications_map.find(id);
    if (it != publications_map.end()) {
        return it->second.title;
    } else {
        return NO_NAME;
    }
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto it = publications_map.find(id);
    if (it != publications_map.end()) {
        return it->second.year;
    } else {
        return NO_YEAR;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto it = publications_map.find(id);
    if ( it != publications_map.end() ) {
        return it->second.affiliations;
    } else {
        return vector<AffiliationID>{NO_AFFILIATION};
    }
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto parent_it = publications_map.find(parentid);
    auto child_it = publications_map.find(id);

    if (parent_it == publications_map.end() || child_it == publications_map.end()) {
        return false;
    }

    if (find(parent_it->second.references.begin(), parent_it->second.references.end(), id) != parent_it->second.references.end()) {
        return false;
    }
    parent_it->second.references.push_back(id);
    backward_references[id].push_back(parentid);

    return true;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto it = publications_map.find(id);

    if ( it == publications_map.end() ) {
        return {NO_PUBLICATION};
    }

    return it->second.references;

}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid) {
    auto affil_it = affiliations_map.find(affiliationid);
    auto pub_it = publications_map.find(publicationid);

    if (affil_it == affiliations_map.end() || pub_it == publications_map.end()) {
        return false;
    }

    // Tarkista, onko affiliaatio jo liitetty julkaisuun
    if (std::find(pub_it->second.affiliations.begin(), pub_it->second.affiliations.end(), affiliationid) != pub_it->second.affiliations.end()) {
        return false; // Affiliaatio jo liitetty tähän julkaisuun
    }

    // Lisää affiliaatio julkaisuun
    pub_it->second.affiliations.push_back(affiliationid);

    // Päivitä shared_publications_count uudelle affiliaatiolle ja olemassa oleville affiliaatioille
    for (const auto& existing_affiliation : pub_it->second.affiliations) {
        if (existing_affiliation != affiliationid) {
            shared_publications_count[affiliationid][existing_affiliation]++;
            shared_publications_count[existing_affiliation][affiliationid]++;

            // Päivitä adjacency_list
            adjacency_list[affiliationid].push_back(existing_affiliation);
            adjacency_list[existing_affiliation].push_back(affiliationid);
        }
    }

    return true;
}



std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    vector<PublicationID> publications_with_affiliation;

    if (affiliations_map.find(id) == affiliations_map.end()) {
        return {NO_PUBLICATION};
    }

    for (const auto& publication_entry : publications_map) {
        const auto& affiliations = publication_entry.second.affiliations;
        if (find(affiliations.begin(), affiliations.end(), id) != affiliations.end()) {
            publications_with_affiliation.push_back(publication_entry.first);
        }
    }
    return publications_with_affiliation;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto it = publications_map.find(id);

    if ( it == publications_map.end() ) {
        return NO_PUBLICATION;
    }

    for ( const auto& publication : publications_map ) {
        if ( find(publication.second.references.begin(),
                      publication.second.references.end(),
                      id) != publication.second.references.end() ) {
            return publication.first;
        }
    }

    return NO_PUBLICATION;
}

vector<pair<Year, PublicationID>> Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    vector<pair<Year, PublicationID>> publications_after;

    auto aff_it = publications_by_affiliation_and_year.find(affiliationid);
    if (aff_it == publications_by_affiliation_and_year.end()) {
        return {{NO_YEAR, NO_PUBLICATION}};
    }

    for (auto year_it = aff_it->second.lower_bound(year); year_it != aff_it->second.end(); ++year_it) {
        for (const auto& pubID : year_it->second) {
            publications_after.emplace_back(year_it->first, pubID);
        }
    }

    sort(publications_after.begin(), publications_after.end(), [](const pair<Year, PublicationID>& a, const pair<Year, PublicationID>& b) {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    });

    return publications_after;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    if (publications_map.find(id) == publications_map.end()) {
        return {NO_PUBLICATION};
    }

    vector<PublicationID> chain;
    unordered_set<PublicationID> visited;
    PublicationID current_id = id;

    while (current_id != NO_PUBLICATION) {
        if (visited.find(current_id) != visited.end()) {
            break;
        }

        visited.insert(current_id);
        auto it = backward_references.find(current_id);

        if (it == backward_references.end() || it->second.empty()) {
            break;
        }

        current_id = it->second.front();
        chain.push_back(current_id);
    }

    return chain;
}

// Here starts the optional functions

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    unordered_set<PublicationID> visited;
    vector<PublicationID> all_references;

    function<void(PublicationID)> dfs = [&](PublicationID current_id) {
        if (visited.find(current_id) != visited.end()) return;

        visited.insert(current_id);

        auto pub_it = publications_map.find(current_id);
        if (pub_it != publications_map.end()) {
            for (const auto& ref_id : pub_it->second.references) {
                all_references.push_back(ref_id);
                dfs(ref_id);
            }
        }
    };

    dfs(id);

    if (all_references.empty() && publications_map.find(id) == publications_map.end()) {
        return {NO_PUBLICATION};
    }

    return all_references;
}

std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    vector<pair<double, AffiliationID>> distances;

    for (const auto& [id, affiliation] : this->affiliations_map) {
        double dist = sqrt((xy.x - affiliation.location.x) * (xy.x - affiliation.location.x) +
                                (xy.y - affiliation.location.y) * (xy.y - affiliation.location.y));
        distances.emplace_back(dist, id);
    }

    sort(distances.begin(), distances.end(), [this](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;

        return this->affiliations_map.at(a.second).location.y < this->affiliations_map.at(b.second).location.y;
    });

    vector<AffiliationID> closest;
    for (int i = 0; i < min(3, static_cast<int>(distances.size())); ++i) {
        closest.push_back(distances[i].second);
    }

    return closest;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    auto aff_it = affiliations_map.find(id);
    if (aff_it == affiliations_map.end()) {
        return false;
    }

    sorted_affiliations.erase(id);
    sorted_by_distance.erase(id);

    auto range = coord_to_affiliation_map.equal_range(aff_it->second.location);
    for (auto i = range.first; i != range.second; ) {
        if (i->second == id) {
            i = coord_to_affiliation_map.erase(i);
        } else {
            ++i;
        }
    }

    all_affiliation_ids.erase(remove(all_affiliation_ids.begin(), all_affiliation_ids.end(), id), all_affiliation_ids.end());

    publications_by_affiliation_and_year.erase(id);

    for (auto& [pub_id, publication] : publications_map) {
        auto& affiliations = publication.affiliations;
        affiliations.erase(remove(affiliations.begin(), affiliations.end(), id), affiliations.end());
    }

    affiliations_map.erase(aff_it);

    is_alphabetical_cache_valid = false;
    is_distance_cache_valid = false;

    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    if (publications_map.find(id1) == publications_map.end() || publications_map.find(id2) == publications_map.end()) {
        return NO_PUBLICATION;
    }

    auto buildPath = [&](PublicationID id, vector<PublicationID>& path) {
        PublicationID current_id = id;
        while (current_id != NO_PUBLICATION) {
            bool found = false;
            for (const auto& [parent_id, pub] : publications_map) {
                if (find(pub.references.begin(), pub.references.end(), current_id) != pub.references.end()) {
                    path.push_back(parent_id);
                    current_id = parent_id;
                    found = true;
                    break;
                }
            }
            if (!found) {
                current_id = NO_PUBLICATION;
            }
        }
    };

    vector<PublicationID> path1, path2;
    buildPath(id1, path1);
    buildPath(id2, path2);

    unordered_set<PublicationID> path1_set(path1.begin(), path1.end());
    for (const auto& id : path2) {
        if (path1_set.find(id) != path1_set.end()) {
            return id;
        }
    }

    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    auto pub_it = publications_map.find(publicationid);
    if (pub_it == publications_map.end()) {
        return false;
    }

    for (auto& [id, publication] : publications_map) {
        auto& refs = publication.references;
        refs.erase(remove(refs.begin(), refs.end(), publicationid), refs.end());

        for (const auto& ref_id : refs) {
            auto& back_refs = backward_references[ref_id];
            back_refs.erase(remove(back_refs.begin(), back_refs.end(), id), back_refs.end());
        }
    }

    for (const auto& aff_id : pub_it->second.affiliations) {
        auto& year_map = publications_by_affiliation_and_year[aff_id];
        auto year_it = year_map.find(pub_it->second.year);
        if (year_it != year_map.end()) {
            auto& pub_ids = year_it->second;
            pub_ids.erase(remove(pub_ids.begin(), pub_ids.end(), publicationid), pub_ids.end());

            if (pub_ids.empty()) {
                year_map.erase(year_it);
            }
        }
     }

    backward_references.erase(publicationid);

    publications_map.erase(pub_it);

    is_alphabetical_cache_valid = false;
    is_distance_cache_valid = false;

    return true;
}

          // --------------- //
          //                 //
          //  PRG2 Funktiot  //
          //                 //
          // --------------- //

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id) {

    std::vector<Connection> connectedAffiliations;

    // Return empty vector if ID doesn't exist in affiliations_map
    if (affiliations_map.find(id) == affiliations_map.end()) {
        return connectedAffiliations;
    }

    std::unordered_map<AffiliationID, int> connectionWeights;
    for (const auto& pubPair : publications_map) {
        const auto& publication = pubPair.second;
        if (std::find(publication.affiliations.begin(), publication.affiliations.end(), id) != publication.affiliations.end()) {
            for (const auto& affilID : publication.affiliations) {
                if (affilID != id) {
                    connectionWeights[affilID]++;
                }
            }
        }
    }

    for (const auto& [affilID, weight] : connectionWeights) {
        connectedAffiliations.push_back({id, affilID, weight});
    }

    return connectedAffiliations;
}

std::vector<Connection> Datastructures::get_all_connections() {

    std::set<Connection, ConnectionComparator> connectionSet;

    for (const auto& [affiliationId, innerMap] : shared_publications_count) {
        for (const auto& [otherAffiliationId, count] : innerMap) {
            if (count > 0) {
                // Ensure aff1 is the smaller ID
                auto [aff1, aff2] = std::minmax(affiliationId, otherAffiliationId);
                connectionSet.insert(Connection{aff1, aff2, count});
            }
        }
    }

    // Convert set to vector and return
    return std::vector<Connection>(connectionSet.begin(), connectionSet.end());
}

std::vector<Connection> Datastructures::get_any_path(AffiliationID source, AffiliationID target) {
    if (source == target) {
        return {}; // No path needed if source and target are the same
    }

    // Use the existing adjacency_list instead of building it again
    // Make sure adjacency_list is being updated correctly elsewhere in your code

    // Step 1: BFS to find the path
    std::queue<AffiliationID> queue;
    std::unordered_map<AffiliationID, AffiliationID> cameFrom;
    std::unordered_set<AffiliationID> visited;
    queue.push(source);
    visited.insert(source);

    while (!queue.empty()) {
        AffiliationID current = queue.front();
        queue.pop();

        if (current == target) {
            // Path found, backtrack to create the path
            std::vector<Connection> path;
            while (current != source) {
                AffiliationID predecessor = cameFrom[current];

                Connection conn;
                conn.aff1 = predecessor;
                conn.aff2 = current;
                conn.weight = shared_publications_count[predecessor][current]; // Get the actual weight

                path.push_back(conn);
                current = predecessor;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : adjacency_list[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                cameFrom[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}


// Vapaaehtoiset PRG2

Path Datastructures::get_path_with_least_affiliations(AffiliationID source, AffiliationID target) {
    if (source == target) {
        return {}; // No path needed if source and target are the same
    }

    if (affiliations_map.find(source) == affiliations_map.end() ||
        affiliations_map.find(target) == affiliations_map.end()) {
        return {}; // Return empty if source or target affiliations don't exist
    }

    // BFS
    std::queue<AffiliationID> queue;
    std::unordered_map<AffiliationID, AffiliationID> cameFrom;
    std::unordered_set<AffiliationID> visited;
    queue.push(source);
    visited.insert(source);

    while (!queue.empty()) {
        AffiliationID current = queue.front();
        queue.pop();

        if (current == target) {
            // Backtrack to create the path
            Path path;
            while (current != source) {
                AffiliationID predecessor = cameFrom[current];

                // Retrieve the weight of the connection
                int weight = shared_publications_count[predecessor][current];

                path.push_back({predecessor, current, weight});
                current = predecessor;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto& neighbor : adjacency_list[current]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                cameFrom[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return {};
}

Path Datastructures::get_path_of_least_friction(AffiliationID source, AffiliationID target) {
    if (source == target) {
        return {};
    }

    std::unordered_map<AffiliationID, PathInfo> pathInfos;
    std::set<AffiliationID> visited;

    auto compare = [&pathInfos](const AffiliationID& a, const AffiliationID& b) {
        const auto& aInfo = pathInfos[a];
        const auto& bInfo = pathInfos[b];
        if (aInfo.minWeight != bInfo.minWeight)
            return aInfo.minWeight < bInfo.minWeight; // Higher minimum weight (less friction) first
        if (aInfo.pathLength != bInfo.pathLength)
            return aInfo.pathLength < bInfo.pathLength; // Fewer connections first
        // Compare AffiliationID values numerically
        return a < b;
    };

    std::priority_queue<AffiliationID, std::vector<AffiliationID>, decltype(compare)> pq(compare);
    pathInfos[source].totalFriction = 0.0;
    pq.push(source);

    while (!pq.empty()) {
        AffiliationID current = pq.top();
        pq.pop();

        if (visited.find(current) != visited.end()) {
            continue;
        }
        visited.insert(current);

        if (current == target) {
            break;
        }

        for (const auto& neighbor : adjacency_list[current]) {
            double weight = shared_publications_count[current][neighbor];
            double friction = weight > 0 ? 1.0 / static_cast<double>(weight) : std::numeric_limits<double>::max();
            double newTotalFriction = pathInfos[current].totalFriction + friction;

            std::cout << "From " << current << " to " << neighbor << " - Weight: " << weight
                      << ", Friction: " << friction << ", New Total Friction: " << newTotalFriction << std::endl;

            auto& neighborInfo = pathInfos[neighbor];
            if (newTotalFriction < neighborInfo.totalFriction ||
                (newTotalFriction == neighborInfo.totalFriction && pathInfos[current].pathLength + 1 < neighborInfo.pathLength)) {
                neighborInfo.totalFriction = newTotalFriction;
                neighborInfo.minWeight = std::min(pathInfos[current].minWeight, static_cast<int>(weight));
                neighborInfo.pathLength = pathInfos[current].pathLength + 1;
                neighborInfo.previous = current;
                pq.push(neighbor);
            }
        }
    }

    // Output the final path for debugging
    std::cout << "Final Path from " << source << " to " << target << ": ";
    for (AffiliationID at = target; at != source && at != NO_AFFILIATION; at = pathInfos[at].previous) {
        if (pathInfos.find(at) == pathInfos.end()) {
            std::cout << "No path found!" << std::endl;
            return {};
        }
        std::cout << at << " <- ";
    }
    std::cout << source << std::endl;

    // Reconstruct the path from target to source
    Path path;
    for (AffiliationID at = target; at != source && at != NO_AFFILIATION; at = pathInfos[at].previous) {
        path.push_back({pathInfos[at].previous, at, shared_publications_count[pathInfos[at].previous][at]});
    }
    std::reverse(path.begin(), path.end());

    return path;
}


PathWithDist Datastructures::get_shortest_path(AffiliationID source, AffiliationID target) {
    if (source == target) {
        return {}; // No path needed if source and target are the same
    }

    std::unordered_map<AffiliationID, int> shortestDistance;
    std::unordered_map<AffiliationID, AffiliationID> prev;

    for (const auto& affil : affiliations_map) {
        shortestDistance[affil.first] = std::numeric_limits<int>::max();
    }
    shortestDistance[source] = 0;

    auto compare = [&shortestDistance](const AffiliationID& a, const AffiliationID& b) {
        return shortestDistance[a] > shortestDistance[b];
    };
    std::priority_queue<AffiliationID, std::vector<AffiliationID>, decltype(compare)> pq(compare);
    pq.push(source);

    while (!pq.empty()) {
        AffiliationID current = pq.top();
        pq.pop();

        if (current == target) {
            break; // Found the target
        }

        for (const auto& neighbor : adjacency_list[current]) {
            int distance = static_cast<int>(sqrt(pow(affiliations_map[neighbor].location.x - affiliations_map[current].location.x, 2) + pow(affiliations_map[neighbor].location.y - affiliations_map[current].location.y, 2)));
            int newDistance = shortestDistance[current] + distance;

            if (newDistance < shortestDistance[neighbor]) {
                shortestDistance[neighbor] = newDistance;
                prev[neighbor] = current;
                pq.push(neighbor);
            }
        }
    }

    PathWithDist path;
    for (AffiliationID at = target; at != source; at = prev[at]) {
        if (prev.find(at) == prev.end()) {
            return {}; // No path found
        }
        int distance = static_cast<int>(sqrt(pow(affiliations_map[at].location.x - affiliations_map[prev[at]].location.x, 2) + pow(affiliations_map[at].location.y - affiliations_map[prev[at]].location.y, 2)));
        int weight = shared_publications_count[prev[at]][at]; // Get the weight of the connection
        path.emplace_back(std::make_pair(Connection{prev[at], at, weight}, distance));
    }
    std::reverse(path.begin(), path.end());
    return path;
}

