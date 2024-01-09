// Datastructures.cc

//

// Student name: Lassi Lappalainen

// Student email: lassi.lappalainen@tuni.fi

// Student number: 150390123

// AI tool used and the version: OpenAI ChatGPT (Version: GPT-4)

// The purpose of the use: Optimizing solutions, finding errors, helping
// with syntax and giving feedback.

// The part(s) where it was utilized: In 'datastructure.hh', it recommended and
// helped with datastructures (and struct...DistanceComparator, AffiliationComparator)
// for the get_affiliations_alphabetically,
// get_affiliations_distance_increasing, find_affiliations_with_coord, so that
// the command count could be decreased. I also used it for couple functions that
// were more difficult to implement and that I didn't have enough knowledge for
// syntax, such as the optional functions, get_all_references, get_closest_common_parent
// and get_affiliations_closest_to. Also for the not optional, get_publications_after
// and change_affiliation_coord. It was also utilized for fixing errors or any
// issues rising.

#include "datastructures.hh"

#include <random>

#include <cmath>

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
    affiliations_map.clear();
    sorted_affiliations.clear();
    sorted_by_distance.clear();
    coord_to_affiliation_map.clear();
    all_affiliation_ids.clear();

    is_alphabetical_cache_valid = false;
    is_distance_cache_valid = false;
    alphabetical_cache.clear();
    distance_cache.clear();

    publications_map.clear();
    backward_references.clear();
    publications_by_affiliation_and_year.clear();
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

    backward_references[id] = vector<PublicationID>();
    publications_map.emplace(id, Publication{id, name, year, {}, affiliations});

    for (const auto& affiliation_id : affiliations) {
        publications_by_affiliation_and_year[affiliation_id][year].push_back(id);
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

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto affil_it = affiliations_map.find(affiliationid);
    auto pub_it = publications_map.find(publicationid);

    if (affil_it == affiliations_map.end() || pub_it == publications_map.end()) {
        return false;
    }

    pub_it->second.affiliations.push_back(affiliationid);
    publications_by_affiliation_and_year[affiliationid][pub_it->second.year].push_back(publicationid);

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
