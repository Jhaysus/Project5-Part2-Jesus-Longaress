//
// Created by Ali A. Kooshesh on 5/9/21.
//

#ifndef HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP
#define HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP

#include<vector>
#include<string>
#include <cstdint>
#include <sstream>



class HashTableDictionary {

    enum ELEMENT_STATUS {AVAILABLE, DELETED, USED};

public:
    enum PROBE_TYPE {SINGLE, DOUBLE};

    HashTableDictionary( std::size_t tableSize_,
        PROBE_TYPE probeType, bool doCompact=true, double compactionTriggerRate=0.95);

    std::int64_t elapsed_ns = 0;   // total replay time (nanoseconds)


    bool insert( const std::string& v );
    bool member( const std::string& v );
    bool remove( const std::string& v);
    [[nodiscard]] bool empty() const;
    [[nodiscard]] std::size_t size() const;
    void printStats() const;
    void printCounts();

    void printMask();
    void printMask(ELEMENT_STATUS status);
    void printBeforeAndAfterCompactionMaps();
    void printActiveDeleteMap();

    void clear();
    std::string csvStats();
    static std::string csvStatsHeader();

    double elapsed_ms() const {
        return static_cast<double>(elapsed_ns) / 1e6;
    }

    //helper
    static std::string csv_header() {
        return "impl,profile,trace_path,N,seed,elapsed_ms,ops_total,average_probes,eff_load_factor_pct,load_factor_pct,tombstones_pct,full_scans,compactions,compaction_state";
    }

    std::string build_csv_row( std::string impl, std::string profile, std::string trace_path, std::size_t N, unsigned seed, double elapsed_ms, std::size_t ops_total, const HashTableDictionary& dict)
    {
        std::ostringstream out;
        out << impl << ","
            << profile << ","
            << trace_path << ","
            << N << ","
            << seed << ","
            << elapsed_ms << ","
            << ops_total << ",";


        return out.str();
    }


private:
    std::size_t  TABLE_SIZE;
    PROBE_TYPE probeType;

    std::vector<std::string> hashTable;
    std::vector<ELEMENT_STATUS> hashTableMask;

    std::vector<char> beforeCompaction, afterCompaction;

    std::size_t primaryHashFunction( const std::string&  v );
    std::size_t secondaryHashFunction( const std::string&  v );
    std::size_t memberHelper( const std::string& v );
    [[nodiscard]] double effectiveLoadFactor() const;

    void compactTable();

    double compactionTriggerEffectiveRate = 0.95;

    bool shouldCompact = false;

    std::int64_t numLookups = 0;
    std::int64_t numDeletes = 0;
    std::int64_t numInserts = 0;

    int numCompactions = 0;

    std::int64_t numHits = 0;
    std::int64_t numMisses = 0;
    std::int64_t numFullScans = 0;

    std::int64_t totalProbes = 0;

    std::int64_t numberOfActive = 0;
    std::int64_t numberOfTombstones = 0;
    std::int64_t maxTombstones = 0;

    std::int64_t maxValuesInTable = 0;

};


#endif //HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP
